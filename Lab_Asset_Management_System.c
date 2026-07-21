#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORKING 0
#define UNDER_REPAIR 1
#define E_WASTE 2
#define HIGH 1
#define MEDIUM 2
#define LOW 3
//Bst ke liye databse hai ye
//typedef use kiya hai taaki Asset a; direct ho
typedef struct Asset{
    int assetID;
    int status;
    int repairCount;
    int labNumber;
    char deviceType[30];
    char brand[30];
    char purchaseDate[20];
    struct Asset *left,*right;
}Asset;
//priority Queue
typedef struct MaintenanceRequest{
    int assetID;
    int priority;
    char complaintDate[20];
    struct MaintenanceRequest *next;
}Request;
//direct request se ascess kar sakte hai;
Asset *root=NULL;
Request *front=NULL;
int nextAssetID=101;
//BST ke saare fucntion idhar se
//insert karne ke liye root jo current hai and node is new
Asset* insertAsset(Asset *root, Asset *node){
    if(root==NULL) return node;
    if(node->assetID < root->assetID)
        root->left=insertAsset(root->left,node);
    else
        root->right=insertAsset(root->right,node);
    return root;
}
//root curret node hai jispe ham hai id check kar rahe hai
Asset* searchAsset(Asset *root,int id){
    if(root==NULL || root->assetID==id) return root;
    if(id<root->assetID) return searchAsset(root->left,id);
    return searchAsset(root->right,id);
}
//LNR hai root root node hai
void displayAssets(Asset *root){
    if(root==NULL) return;
    displayAssets(root->left);
    printf("\nID:%d  Type:%s  Brand:%s  Lab:%d  Repairs:%d  Status:%d",
           root->assetID,root->deviceType,root->brand,
           root->labNumber,root->repairCount,root->status);
    displayAssets(root->right);
}
// smallest leaf node for inorder successor
Asset* minValueNode(Asset *node){
    while(node && node->left!=NULL) node=node->left;
    return node;
}

Asset* deleteAsset(Asset *root,int id){
    if(root==NULL) return root;//notfound

    if(id<root->assetID)//go left
        root->left=deleteAsset(root->left,id);
    else if(id>root->assetID)//go right
        root->right=deleteAsset(root->right,id);
    else{
        if(root->left==NULL){//no left child hai
            Asset *temp=root->right;
            free(root);//delete required node and point child->parent
            return temp;
        }
        else if(root->right==NULL){//no right child
            Asset *temp=root->left;
            free(root);
            return temp;
        }

        Asset *temp=minValueNode(root->right);
//smallest right subtree nikal
//temp point karo
        root->assetID=temp->assetID;
        strcpy(root->deviceType,temp->deviceType);
        strcpy(root->brand,temp->brand);
        root->labNumber=temp->labNumber;
        strcpy(root->purchaseDate,temp->purchaseDate);
        root->status=temp->status;
        root->repairCount=temp->repairCount;
//temp ka date root mai paste karo and temp node delete karo
        root->right=deleteAsset(root->right,temp->assetID);
    }
    return root;
}

//Priority Queue

void enqueueRequest(int assetID,char date[],int priority){
    Request *newNode=(Request*)malloc(sizeof(Request));
    newNode->assetID=assetID;
    strcpy(newNode->complaintDate,date);
    newNode->priority=priority;
    newNode->next=NULL;
//copy data from bst
    if(front==NULL || priority<front->priority){//if queue is empty or higher then node is front
        newNode->next=front;
        front=newNode;
        return;
    }

    Request *temp=front;//for middle to add queue
    while(temp->next!=NULL && temp->next->priority<=priority)
        temp=temp->next;

    newNode->next=temp->next;
    temp->next=newNode;
}

Request* dequeueRequest(){
    if(front==NULL) return NULL;//empty queue
    Request *temp=front;//saves fornt node
    //moves to next node
    //delete saved note
    front=front->next;
    return temp;
}

void displayQueue(){
    Request *temp=front;
    while(temp){
        printf("\nAsset:%d Priority:%d Date:%s",
        temp->assetID,temp->priority,temp->complaintDate);
        temp=temp->next;
    }
}

//takes input and registers in bst

void registerDevice(){
    Asset *node=(Asset*)malloc(sizeof(Asset));

    node->assetID=nextAssetID++;

    printf("Device Type: ");
    scanf("%s",node->deviceType);

    printf("Brand: ");
    scanf("%s",node->brand);

    printf("Lab Number: ");
    scanf("%d",&node->labNumber);

    printf("Purchase Date: ");
    scanf("%s",node->purchaseDate);

    node->status=WORKING;
    node->repairCount=0;
    node->left=node->right=NULL;

    root=insertAsset(root,node);

    printf("\nAsset Registered. ID=%d\n",node->assetID);
}

void raiseMaintenanceRequest(){
    int id,priority;
    char date[20];

    printf("Asset ID: ");
    scanf("%d",&id);
//verify id
    Asset *asset=searchAsset(root,id);

    if(asset==NULL){
        printf("Device Not Found\n");
        return;
    }
//checks status
    if(asset->status!=WORKING){
        printf("Device Not Available\n");
        return;
    }
//date
    printf("Complaint Date: ");
    scanf("%s",date);
//determine priority
    if(strcmp(asset->deviceType,"Server")==0)
        priority=HIGH;
    else if(strcmp(asset->deviceType,"Projector")==0)
        priority=MEDIUM;
    else
        priority=LOW;

    enqueueRequest(id,date,priority);

    asset->status=UNDER_REPAIR;

    printf("Maintenance Request Added\n");
}

void processMaintenance(){
    //removes highest priority device
    Request *req=dequeueRequest();
    if(req==NULL){
        printf("No Pending Requests\n");
        return;
    }

    Asset *asset=searchAsset(root,req->assetID);
    //asset id

    int choice;

    printf("\nProcessing Asset %d\n",asset->assetID);
    printf("Repairable? (1-Yes 0-No): ");
    scanf("%d",&choice);

    if(choice==1){
        asset->repairCount++;
        asset->status=WORKING;
        printf("Device Repaired\n");
    }
    else{
        printf("CSR/EPR Available? (1-Yes 0-No): ");
        scanf("%d",&choice);

        if(choice==1){
            printf("Enter New Brand: ");
            scanf("%s",asset->brand);

            printf("Enter New Purchase Date: ");
            scanf("%s",asset->purchaseDate);

            asset->repairCount=0;
            asset->status=WORKING;

            printf("Replacement Updated\n");
        }
        else{
            asset->status=E_WASTE;
            printf("Moved to E-Waste\n");
        }
    }

    free(req);
}

int wasteIDs[500],countWaste;

void collectWaste(Asset *root){//collect e=waste id in bst
    if(root==NULL) return;
    collectWaste(root->left);
    if(root->status==E_WASTE)
        wasteIDs[countWaste++]=root->assetID;
    collectWaste(root->right);
}

void clearEWaste(){
    countWaste=0;
    collectWaste(root);
//clear e-waste
    for(int i=0;i<countWaste;i++)
        root=deleteAsset(root,wasteIDs[i]);
        //delete one assets at a time

    printf("%d E-Waste Assets Deleted\n",countWaste);
}

int main(){
    int ch;

    do{
        printf("\n1.Register Device");
        printf("\n2.Display Assets");
        printf("\n3.Raise Maintenance");
        printf("\n4.Display Queue");
        printf("\n5.Process Maintenance");
        printf("\n6.Clear E-Waste");
        printf("\n0.Exit");

        printf("\nChoice: ");
        scanf("%d",&ch);

        switch(ch){
            case 1: registerDevice(); break;
            case 2: displayAssets(root); break;
            case 3: raiseMaintenanceRequest(); break;
            case 4: displayQueue(); break;
            case 5: processMaintenance(); break;
            case 6: clearEWaste(); break;
        }

    }while(ch!=0);

    return 0;
}
