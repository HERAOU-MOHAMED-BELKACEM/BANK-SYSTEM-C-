#include<iostream>
#include<ctime>
#include<cmath>
#include<string>
#include<cstdio>
#include<vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;
string fileofbank = "bank.txt";




struct STclientdata {
	string account_number;
	string pincode;
	string full_name;
	string phone;
	double acountbalance;
	bool markfordelete = false;
	bool markforupdate = false;
};
string joinstring(vector<string> vstring, string delma)
{
	string m = "";
	for (string& l : vstring)
	{
		m = m + l + delma;
	}
	return m.substr(0, m.length() - delma.length());
}
vector<string> splitstring(string m, string delim)
{
	vector<string> vsplit;
	short pos = 0;
	string word;
	int counter = 0;
	while ((pos = m.find(delim)) != std::string::npos)
	{
		word = m.substr(0, pos);
		if (word != "")
		{
			vsplit.push_back(word);
			counter++;
		}
		m.erase(0, pos + delim.length());
	}
	if (m != "")
	{
		vsplit.push_back(m);
		counter++;
	}

	return vsplit;
}
int ReadPositiveNumber(const string& message)
{
	int number;
	do
	{
		cout << message << endl;
		cin >> number;
	} while (number <= 0);
	return number;
}

STclientdata readdata(STclientdata& info)
{
	cout << "enter client account number : " << "";
	getline(cin >> ws, info.account_number);
	cout << "enter client PinCode : " << "";
	getline(cin, info.pincode);
	cout << "enter client Full Name : " << "";
	getline(cin, info.full_name);
	cout << "enter client Phone number : " << "";
	getline(cin, info.phone);
	cout << "enter client account balance : " << "";
	cin >> info.acountbalance;
	return info;

}


vector<string> insertdata(STclientdata info)
{
	vector<string> vinser;
	vinser.push_back(info.account_number);
	vinser.push_back((info.pincode));
	vinser.push_back(info.full_name);
	vinser.push_back((info.phone));
	vinser.push_back(to_string(info.acountbalance));
	return vinser;
}
string add_data_to_line(STclientdata info)
{
	vector<string> vinser;
	vinser = insertdata(info);

	string k = joinstring(vinser, "#--#");
	return k;
}

void data_line_to_file(string filename, string dataline)
{
	fstream bankfile;
	bankfile.open(filename, ios::out | ios::app);
	if (bankfile.is_open())
	{
		bankfile << dataline << endl;
		bankfile.close();
	}
}
void addnewclients()
{

	STclientdata info;
	readdata(info);
	data_line_to_file(fileofbank, add_data_to_line(info));

}



void addclients()
{
	char addmore = 'Y';
	do
	{
		system("cls");
		cout << "Add New Clients" << endl;
		addnewclients();

		cout << "Clients was added succsesfuly do you want to add more (y/n) : " << endl;
		cin >> addmore;
	} while (toupper(addmore) == 'Y');
}
STclientdata convert_line_to_record(string line)
{
	STclientdata client;
	vector<string> vline;
	vline = splitstring(line, "#--#");
	client.account_number = vline.at(0);
	client.pincode = vline.at(1);
	client.full_name = vline.at(2);
	client.phone = vline.at(3);
	client.acountbalance = stod(vline.at(4));
	return client;
}

vector<STclientdata> STinfos(string  filename)
{
	vector<STclientdata> VData;
	fstream myfile;
	myfile.open(filename, ios::in);
	if (myfile.is_open())
	{
		string line;
		STclientdata client;

		while (getline(myfile, line))
		{
			client = convert_line_to_record(line);
			VData.push_back(client);
		}
		myfile.close();

	}
	return VData;
}
bool markclientfordelete(vector<STclientdata>& VData, string accountnumber)
{
	for (STclientdata& c : VData)
	{
		if (c.account_number == accountnumber)
		{
			c.markfordelete = true;
			return true;
		}
	}
	return false;
}

vector<STclientdata> save_new_data_tofile(vector<STclientdata> VData, string filename)
{
	fstream myfile;
	myfile.open(filename, ios::out);
	if (myfile.is_open())
	{
		STclientdata client;
		string line;
		for (STclientdata client : VData)

		{
			if (client.markfordelete == false)
			{
				line = add_data_to_line(client);
				myfile << line << endl;
			}
		}
		myfile.close();
	}
	return VData;
}
void print_client_data(STclientdata client)
{
	//cout << "________________________________________________________________________________________________________________________________";
	cout << "| " << setw(15) << client.account_number;
	cout << "| " << setw(10) << client.pincode;
	cout << "| " << setw(40) << client.full_name;
	cout << "| " << setw(12) << client.phone;
	cout << "| " << setw(12) << client.acountbalance;
}

void print_all_clients_data(vector<STclientdata> VData)
{
	cout << "________________________________________________________________________________________________________________________________";
	cout << "\n\t\t\t\t\tClient List (" << VData.size() << ")Client(s). ";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (STclientdata client : VData)
	{
		print_client_data(client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}
string read_account_number()
{
	string accountnumber;
	cout << "enter client's account number" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, accountnumber);
	return accountnumber;
}
bool find_client_by_account_number(STclientdata& client, string acoountnumber, vector<STclientdata> VData)
{
	for (STclientdata c : VData)
	{
		if (c.account_number == acoountnumber)
		{
			client = c;
			return true;
		}
	}
	return false;
}

bool delete_client_by_account_number(vector<STclientdata>& VData, string accountnumber)
{
	STclientdata client;
	char answer = 'n';
	if (find_client_by_account_number(client, accountnumber, VData))
	{
		print_client_data(client);
		cout << "\n\nare you sure you want to delete client's info (y/n)" << " ";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			markclientfordelete(VData, accountnumber);
			save_new_data_tofile(VData, fileofbank);
			//refresh clients
			VData = STinfos(fileofbank);

			cout << "client was deleted succesfully" << endl;
			return true;

		}
	}
	else
	{
		cout << "client number " << accountnumber << " not found" << endl;
		return false;
	}
}
bool check_clients_update_answer(vector<STclientdata>& VData, string accountnumber)
{

	for (STclientdata& client : VData)
	{
		if (client.account_number == accountnumber)
		{
			char answer = 'n';
			cout << "do u want to update clients info ? (y/n) : ";
			cin >> answer;
			if (toupper(answer) == 'Y')
			{
				client.markforupdate = true;
				return true;

			}

		}

	}
	return false;
}
vector<STclientdata> update_file_data(STclientdata& client, vector<STclientdata>& VData, string accountnumber)
{
	char n;
	if (find_client_by_account_number(client, accountnumber, VData))
	{
		print_client_data(client);
		cout << "\nDo you want to update client info ? : " << "";
		cin >> n;
		if (n == 'y' || n == 'Y')
		{
			for (STclientdata& client : VData)
			{
				if (client.account_number == accountnumber)
				{
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "pincode          : ";
					getline(cin, client.pincode);
					cout << "full name        : ";
					getline(cin, client.full_name);
					cout << "phone number     : ";
					getline(cin, client.phone);
					cout << " account balance : ";
					cin>> client.acountbalance;
				}
			}


		}
	}
	return VData;
}

void Change_The_PERSON_INFO(STclientdata& client, vector<STclientdata>& VData, string accountnumber)
{

	string line;
	if (!find_client_by_account_number(client, accountnumber, VData))
	{

		cout << "account number not found ";
	}
	else
	{
		if (!check_clients_update_answer(VData, accountnumber))
		{
			cout << "you chosed no ";

		}
		else
		{
			update_file_data(client, VData, accountnumber);
			for (STclientdata c : VData)
			{
				line = add_data_to_line(c);
				cout << line << endl;
			}

		}

	}

}
vector<STclientdata> Save_New_Data(vector<STclientdata> VData, string filename)
{
	fstream myfile;
	myfile.open(filename, ios::out);
	if (myfile.is_open())
	{
		STclientdata client;
		string line;
		for (STclientdata client : VData)

		{
			line = add_data_to_line(client);
			myfile << line << endl;
		}
		myfile.close();
	}
	return VData;
}
void Main_Menu(vector<STclientdata> VData)
{
	STclientdata client;
	;
	int number;
	do
	{
		cout << "===============================================================================================================" << endl;
		cout << "\t\t\t\t" << "MAIN MENU SCREEN" << endl;
		cout << "===============================================================================================================" << endl;
		cout << "\t" << "[1] SHOW CLIENTS LIST" << endl;
		cout << "\t" << "[2] ADD NEW CLIENT" << endl;
		cout << "\t" << "[3] DELETE CLIENT" << endl;
		cout << "\t" << "[4] UPDATE CLIENT INFOS" << endl;
		cout << "\t" << "[5] FIND CLIENT" << endl;
		cout << "\t" << "[6] EXIT" << endl;
		cout << "===============================================================================================================" << endl;
		cout << "choose what u want to do : " << endl;

		cin >> number;

	} while (number < 1 || number > 6);

	if (number == 1)
	{
		system("cls");
		char n;
		do
		{
			print_all_clients_data(VData);
			cout << "press B to go back to main menu : " << "";
			cin >> n;
		} while (n != 'B' && n != 'b');
		system("cls");
		Main_Menu(VData);
	}
	if (number == 2)
	{
		system("cls");
		char n;
		do
		{
			addclients();
			cout << "press B to go back to main menu : " << "";
			cin >> n;
		} while (n != 'B' && n != 'b');
		system("cls");
		VData = STinfos(fileofbank);
		Main_Menu(VData);
	}
	if (number == 3)
	{
		system("cls");
		char n;
		do
		{
			string a = read_account_number();
			find_client_by_account_number(client, a, VData);
			delete_client_by_account_number(VData, a);
			cout << "press B to go back to main menu : " << "";
			cin >> n;
		} while (n != 'B' && n != 'b');
		system("cls");
		VData = STinfos(fileofbank);
		Main_Menu(VData);
	}
	if (number == 4)
	{
		system("cls");
		char n;
		do
		{
			string a = read_account_number();
			find_client_by_account_number(client, a, VData);
			update_file_data(client, VData, a);
			cout << "press B to go back to main menu : " << "";
			cin >> n;
		} while (n != 'B' && n != 'b');
		Save_New_Data(VData, fileofbank);
		system("cls");
		Main_Menu(VData);
	}
	if (number == 5)
	{
		system("cls");
		char n;
		do
		{
			string a = read_account_number();
			find_client_by_account_number(client, a, VData);
			print_client_data(client);
			cout << "\npress B to go back to main menu : " << "";
			cin >> n;
		} while (n != 'B' && n != 'b');
		system("cls");
		Main_Menu(VData);


	}
	if (number == 6)
	{
		exit(0);
	}
}



int main()
{
	STclientdata client;
	vector<STclientdata> VData = STinfos(fileofbank);
	Main_Menu(VData);
	return 0;

}
