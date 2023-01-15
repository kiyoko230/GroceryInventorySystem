#include <iostream>
#include <iomanip>
#include "Item.h"
#include "List.h"
#include <string>
#include <vector>
using namespace std;

int main() {
	Item item;
	List<Item> manage;
	int select,sortSelect;
	bool exit = false;
	string itemToRestock;

	manage.readFromFile(); // read the data in the item excel file
	do {
		cout << "Welcome to Grocery Inventory System\n" // menu for the user to choose the function
			<< "1. Add item\n"
			<< "2. Display item\n"
			<< "3. Sort items\n"
			<< "4. Search items\n"
			<< "5. Restock items\n"
			<< "6. Exit\n"
			<< "Pleae select your option: ";
		cin >> select;
		cout << endl;
		while (cin.fail() || select <=0 || select > 6) // check the validation of the input
		{
			cin.clear();
			cin.ignore(10,'\n');
			cout << "Invallid Option\n"
				<< "Please select your option again : ";
			cin >> select;
			cout << endl;
		}
		if (select == 1) 
		{
			manage.addItem(); // call the addItem function in List class
			cout << "The item is added successfully!\n\n";
			
		}
		else if (select == 2) 
		{
			manage.displayItem(); //call the displayItem function in List class
		}
		else if (select == 3)
		{
			cout << "Sort Condition:\n"
				<< "1. Item ID\n"
				<< "2. Item Name\n"
				<< "3. Item Price(RM)\n"
				<< "4. Item Quantity\n"
				<<"Please select the sort condition: ";
			cin >> sortSelect;
			while (cin.fail() || select <= 0 || select > 4) // check the validation of the input
			{
				cin.clear();
				cin.ignore(10, '\n');
				cout << "Invallid Option\n"
					<< "Please select your sort condition again : ";
				cin >> select;
				cout << endl;
			}
			manage.sortItems(sortSelect); // call sort function to sort the items
			cout << "The items are sorted successfully!\n";
			cout << endl;
			
			
		}
		else if (select == 4)//search item
		{

			if (manage.numberOfItem() == 0)//check if there is no item in the list
			{
				cout << "There is no item in the inventory!" << endl;
			}
			else
			{
				bool foundStatus = false;
				vector<Item> searchResult;
				int searchBy;

				cout << endl << "1.Item ID "
					<< endl << "2.Item Name"
					<< endl << "3.Item Price"
					<< endl << "4.Item Quantity"
					<< endl << "5.Item Type"
					<< endl << "6.Cancel"
					<< endl << "Search By: ";
				cin >> searchBy;

				while (cin.fail() || searchBy <= 0 || searchBy > 6)// check the validation of the input
				{
					cin.clear();
					cin.ignore(10, '\n');
					cout << "Invallid Option\n"
						<< "Please enter search condition again: ";
					cin >> searchBy;
					cout << endl;
				}

				if (searchBy != 6)
				{
					if (searchBy == 1 || searchBy == 2 || searchBy == 5)//search by item name or item id
					{
						string search;
						if (searchBy == 1)
						{
							cout << "Enter Item ID: ";
							cin >> search;
						}
						else if (searchBy == 2)
						{
							cout << "Enter Item Name: ";
							cin >> search;
						}
						else if (searchBy == 5)
						{
							cout << "Enter Item Type( F-Food / D-Drink): ";
							cin >> search;
						}
						manage.searchItem(search, searchBy, searchResult, foundStatus);

					}
					else if (searchBy == 3)//search by price
					{
						double min, max;
						cout << "Enter minimum price: RM ";
						cin >> min;
						cout << "Enter maximum price: RM ";
						cin >> max;
						manage.searchItem(min, max, searchResult, foundStatus);
					}
					else if (searchBy == 4)//search by quantity
					{
						int min, max;
						cout << "Enter minimum quantity: ";
						cin >> min;
						cout << "Enter maximum quantity: ";
						cin >> max;
						manage.searchItem(min, max, searchResult, foundStatus);
					}

					if (foundStatus)
					{
						//display items found
						cout << endl << "Search result: " << endl;
						cout << setfill('-') << setw(102) << " " << endl;
						cout << "|" << setfill(' ') << setw(10) << left << "Item ID "
							<< "|" << setfill(' ') << setw(20) << left << "Item Name "
							<< "|" << setfill(' ') << setw(8) << left << "Type "
							<< "|" << setfill(' ') << setw(15) << left << "Arrival Date "
							<< "|" << setfill(' ') << setw(15) << left << "Expired Date "
							<< "|" << setfill(' ') << setw(15) << left << "Price(RM) "
							<< "|" << setfill(' ') << setw(10) << left << "Quantity "
							<< "|" << endl;
						cout << setfill('-') << setw(102) << right << " " << endl;

						for (int i = 0; i < searchResult.size(); i++) {
							cout << "|" << setfill(' ') << setw(10) << left << searchResult[i].getItemID()
								<< "|" << setfill(' ') << setw(20) << left << searchResult[i].getItemName()
								<< "|" << setfill(' ') << setw(8) << left << searchResult[i].getItemType()
								<< "|" << setfill(' ') << setw(15) << left << searchResult[i].getArrivalDate()
								<< "|" << setfill(' ') << setw(15) << left << searchResult[i].getExpireDate()
								<< "|" << setfill(' ') << setw(15) << fixed << setprecision(2) << left << searchResult[i].getItemPrice()
								<< "|" << setfill(' ') << setw(10) << left << searchResult[i].getItemQuantity()
								<< "|" << endl;
							cout << setfill('-') << setw(102) << right << " " << endl;
						}
						cout << searchResult.size() << " item(s) found." << endl;
					}
					else
					{
						//searched item doesn't exist
						cout << endl << "No item found."<<endl;
					}
				}
				cout << endl;
			}
		}
		else if (select == 5) { 
			if (manage.numberOfItem() == 0) {
				cout << "There is no item in the inventory!" << endl << endl;
			}
			else {
				cout << "Enter the itemID or itemName of the item you wish to restock: ";
				getline(cin, itemToRestock);
				cout << endl;
				if (manage.restockItems(itemToRestock) == false) {
					cout << "No item match your description!\n\n";
				}
			}
		}
		else {
			cout << "The system success to exit!\n";
			exit = true;
		}
	} while (!exit);
	manage.writeToFile(); // insert the data into item excel file
	cout << "You can check the details in item excel file!\n\n";
	return 0;
}
