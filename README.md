# Lab-asset-management
````markdown
# 🖥️ Lab Asset Management System

A C-based Lab Asset Management System that helps educational institutions manage laboratory assets throughout their lifecycle. The system tracks devices from procurement to disposal while maintaining repair records, refurbishment history, and supporting sustainable e-waste management practices.

---

## 📌 Overview

Managing laboratory equipment manually can lead to poor asset tracking, missing maintenance records, and improper disposal of electronic waste. This project provides a simple command-line solution to manage IT assets efficiently while promoting responsible e-waste disposal.

---

## ✨ Features

- Generate unique Asset IDs
- Add, update, and delete asset records
- Assign devices to laboratories
- Search assets by ID or device type
- Track maintenance and repair history
- Record refurbishment details
- Update asset status
- Maintain disposal records
- Support EPR/CSR-based e-waste workflow
- Store data using file handling

---

## ♻️ E-Waste Management Workflow

1. Device is purchased and assigned a unique Asset ID.
2. Asset details are stored in the database.
3. Device is assigned to a laboratory.
4. If the device fails, a maintenance request is created.
5. IT department checks whether the device can be repaired.
6. If repairable:
   - Repair details are recorded.
   - Device is returned to service.
7. If not repairable:
   - Check if refurbishment is possible.
   - If refurbished, update records and reassign.
8. If refurbishment is not possible:
   - Securely wipe data.
   - Check EPR/CSR eligibility.
   - Send to an authorized e-waste recycler.
   - Update disposal records.

---

## 🛠️ Technologies Used

- **Language:** C
- **Concepts:** Structures, Functions, Arrays
- **Storage:** File Handling
- **Platform:** Console Application

---

## 📂 Project Structure

```
Lab-Asset-Management/
│
├── main.c
├── assets.dat
├── README.md
└── screenshots/
```

---

## 🚀 Future Improvements

- User authentication
- GUI version
- SQL database integration
- Barcode/QR code support
- Report generation
- Web-based dashboard
- Cloud database integration

---

## 🎯 Objective

To provide a simple, efficient, and sustainable solution for managing laboratory assets while ensuring proper maintenance, refurbishment, and environmentally responsible e-waste disposal.

---

## 👨‍💻 Author

**Shreyash Srivastava**

---

## 📄 License

This project is intended for educational purposes.
````
