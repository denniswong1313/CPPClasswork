
#include <iostream>
#include <string>
using namespace std;

int main()
{
	//Declare variables
	int numberofDownloads;
	string ApplicationName;
	double SalesPrice;
	double Tax;
	char CorporateClient;
	double LicensingFee;
	int checkErrors = 1;

	//Ask user for sales information.
	cout << "Number of downloads: ";
	cin >> numberofDownloads;
	cin.ignore(10000, '\n');
	cout << "Application name: ";
	getline(cin, ApplicationName);
	cout << "Sales price: ";
	cin >> SalesPrice;
	cout << "Tax: ";
	cin >> Tax;
	cout << "Corporate client? (y/n): ";
	cin >> CorporateClient;

	//Licensing fee computations
	if (numberofDownloads <= 400)
	{
		LicensingFee = .082 * numberofDownloads * (SalesPrice - Tax);
	}

	if (numberofDownloads > 400 && numberofDownloads <= 1500 && CorporateClient == 'y')
	{
		LicensingFee = (0.082 * 400 * (SalesPrice - Tax)) + (0.142 * (numberofDownloads - 400) * (SalesPrice - Tax));
	}

	if (numberofDownloads > 400 && numberofDownloads <= 1500 && CorporateClient == 'n')
	{
		LicensingFee = (0.082 * 400 * (SalesPrice - Tax)) + (0.115 * (numberofDownloads - 400) * (SalesPrice - Tax));
	}

	if (numberofDownloads > 1500 && CorporateClient == 'y')
	{
		LicensingFee = (0.082 * 400 * (SalesPrice - Tax)) + (0.142 * 1100 * (SalesPrice - Tax)) + (0.148 * (numberofDownloads - 1500) * (SalesPrice - Tax));
	}

	if (numberofDownloads > 1500 && CorporateClient == 'n')
	{
		LicensingFee = (0.082 * 400 * (SalesPrice - Tax)) + (0.115 * 1100 * (SalesPrice - Tax)) + (0.148 * (numberofDownloads - 1500) * (SalesPrice - Tax));
	}

	//Check errors
	if (numberofDownloads < 0)
	{
		cout << "---\n" "The number of downloads sold must be nonnegative.";
		checkErrors = 0;
	}

	if (ApplicationName == "")
	{
		cout << "---\n" "You must enter an application name.";
		checkErrors = 0;
	}

	if (SalesPrice < Tax)
	{
		cout << "---\n" "The sales price must not be less than the tax.";
		checkErrors = 0;
	}

	
	if (Tax < 0)
	{
		cout << "---\n" "The tax must be nonnegative.";
		checkErrors = 0;
	}

	if ( !(CorporateClient == 'y' || CorporateClient == 'n'))
	{ 
		cout << "---\n" "You must enter y or n.";
		checkErrors = 0;
	}

		
	cout.setf(ios::fixed);
        cout.precision(2);

	//Display licensing fee
	if (checkErrors)
	{
		cout << "---\n" << ApplicationName << " needs $" << LicensingFee << " in licensing fees.";
	}

	cin >> ApplicationName;

	return 0;
}