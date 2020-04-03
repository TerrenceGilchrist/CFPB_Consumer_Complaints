#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;


struct Companies {
string 	name;
int		complaintcount;
};


struct Products {
string 	name;
int		productcount;
vector<Companies> company;
};


struct Years {
string year;
vector<Products> product;
};


class Complaints {

public:
void Reading_Data(string&, vector<string>&);
void Filing_Data();
void Counting_Data(string&);
void Output_Data(string&);

private:
ifstream 			File;
ofstream 			New_File;
char 				field, ofield = '\0';
int 				i, j, date_column, company_column, position, product_column;
Companies			Corporation;
Products			ConsumerProduct;
Years 				FY18, FY19, FY20;
string				header_column, company_name, date_name, part_date_name, product_name;
vector<int> 		product_complaintcount;
vector<string> 		header, header_names, company_set, product_set;
vector<string>::iterator    CP;
};



int main ( char* argv[] ) {

string INPUT_PATH = argv[0];
string OUTPUT_PATH = argv[1];

//Declaring the Data Object
Complaints ConsumerComplaints;

//Declaring Header Names to Find
vector<string>		various_header_names;
various_header_names.push_back("Date received");
various_header_names.push_back("Product");
various_header_names.push_back("Company");

cout << "Zero\t" << '\t';
//Reading the Data
ConsumerComplaints.Reading_Data(INPUT_PATH, various_header_names);

//Filing the Data
ConsumerComplaints.Filing_Data();

//Counting the Data
ConsumerComplaints.Counting_Data(INPUT_PATH);

//Output of Data
ConsumerComplaints.Output_Data(OUTPUT_PATH);
}


void Complaints :: Reading_Data (string& input_path, vector<string>& header_names) {

char	COMMA_DELIMITER = static_cast<char>(',');
char	QUOTATION_DELIMITER = static_cast<char>('"');

position = 0;

File.open(input_path);



cout << '\t' << COMMA_DELIMITER << '\t' << QUOTATION_DELIMITER << '\n';

while (File.peek() != '\n') {

field = static_cast<char>(File.get());
cout << field << '\n';

if 		(field == COMMA_DELIMITER) 	{header.push_back(header_column); header_column.clear(); }
else if ( File.peek() == '\n' )		{header_column += string(1,field), header.push_back(header_column), header_column.clear();}
else								{header_column += string(1,field);}
}

cout << '\n' << "header_names.at(0)\t" << header_names.at(0);
cout << '\n' << "header_names.at(1)\t" << header_names.at(1);
cout << '\n' << "header_names.at(2)\t" << header_names.at(2);

cout << '\n' << "header[0]\t" << header[0];
cout << '\n' << "header[1]\t" << header[1];

cout << '\n' << '\n' << header.size();


i = 0;
while (i < header.size()) {
if (header[i].compare(header_names.at(0)) == 0)		{date_column = i;}
i++;
}

cout << '\n' << "date_column\t" << date_column;

i = 0;
while (i < header.size()) {
if (header[i].compare(header_names.at(1)) == 0)		{product_column = i;}
i++;
}

cout << '\n' << "product_column\t" << product_column;

i = 0;
while (i < header.size()) {
if (header[i].compare(header_names.at(2)) == 0)		{company_column = i;}
i++;
}


cout << '\n' << "company_column\t" << company_column;
cout << '\n' << '\n' << "2" << '\t';


position = 0;
while ( !File.eof() ) {

	field = static_cast<char>(File.get());

		if 			( field == COMMA_DELIMITER  )   					{ cout << '\n' << '\n' << position; position++; }
		if  	   	( field == '\n' )														{ cout << '\n' << "position\n"; position = 0; }
        if          ( File.peek() == char_traits<char>::eof() )   							{ cout << '\n' << "Finished\n"; break; }


		if (position == product_column)
		{	while (position < (product_column+1)) {
				ofield = static_cast<char>(File.get()); field = tolower(ofield);
                if			( field == COMMA_DELIMITER && isalpha(File.peek()) )			{position++; product_set.push_back(product_name); product_name.clear();}
				else if		( ispunct(field) )													{product_name += string(1,field);}
				else if     ( isalpha(field) )													{product_name += string(1,field);}
				else if     ( isspace(field) )													{product_name += string(1,field);}
			}
		}


		if (position == company_column)
		{	while (position < (company_column+1)) {
				ofield = static_cast<char>(File.get()); field = toupper(ofield);
				if 	( field == QUOTATION_DELIMITER && File.peek() == COMMA_DELIMITER)   {position++; company_name += string(1,field); company_set.push_back(company_name); company_name.clear();}
				else if 	( field == COMMA_DELIMITER && isalpha(File.peek()) )				{position++; company_set.push_back(company_name); company_name.clear();}
				else if	    ( ispunct(field) )													{company_name += string(1,field);}
				else if     ( isalpha(field) )													{company_name += string(1,field);}
				else if     ( isspace(field) )													{company_name += string(1,field);}
				}
		}

}

File.close();


i=0; cout << '\n' << "product_set.size\t" << product_set.size() << '\n' << '\n';
while (i < product_set.size()) {cout << '\n' << product_set.at(i); i++;}

cout << '\n' << '\n';
i=0; cout << '\n' << "company_set.size\t" << company_set.size() << '\n' << '\n';
while (i < company_set.size()) {cout << '\n' << company_set.at(i); i++;}


}


void Complaints :: Filing_Data() {

CP = unique(company_set.begin(), company_set.end());
company_set.resize( distance(company_set.begin(),CP) );
sort(company_set.begin(), company_set.end());

CP = unique(product_set.begin(), product_set.end());
product_set.resize( distance(product_set.begin(),CP) );
sort(product_set.begin(), product_set.end());


i=0; cout << '\n' << "product_set.size\t" << product_set.size() << '\n' << '\n';
while (i < product_set.size()) {cout << '\n' << product_set.at(i); i++;}

cout << '\n' << '\n';
i=0; cout << '\n' << "company_set.size\t" << company_set.size() << '\n' << '\n';
while (i < company_set.size()) {cout << '\n' << company_set.at(i); i++;}


i=0; j=0;
while (i < product_set.size()) {
	ConsumerProduct.name = product_set[i++];
	ConsumerProduct.productcount = 0;

	while (j < company_set.size()) {
	Corporation.name = company_set[j++];
	Corporation.complaintcount = 0;
	ConsumerProduct.company.push_back(Corporation);
	} j=0;

	FY18.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY18.year = "2018";
}


i=0; j=0;
while (i < product_set.size()) {
	ConsumerProduct.name = product_set[i++];
	ConsumerProduct.productcount = 0;

	while (j < company_set.size()) {
	Corporation.name = company_set[j++];
	Corporation.complaintcount = 0;
	ConsumerProduct.company.push_back(Corporation);
	} j=0;

	FY19.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY19.year = "2019";
}

i=0; j=0;
while (i < product_set.size()) {
	ConsumerProduct.name = product_set[i++];
	ConsumerProduct.productcount = 0;

	while (j < company_set.size()) {
	Corporation.name = company_set[j++];
	Corporation.complaintcount = 0;
	ConsumerProduct.company.push_back(Corporation);
	} j=0;

	FY20.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY20.year = "2020";
}

i=0; j=0;
cout << '\n' << '\n';
while (i < FY18.product.size())	{
        cout << '\n' << FY18.product[i].name << '\t' << FY18.product[i].productcount;
         cout << '\n' << "FY18.product[i].company.size()\t" << FY18.product[i].company.size() << '\n';
        while (j < FY18.product[i].company.size()) {
            cout << FY18.product[i].company[j].name << '\t' << FY18.product[i].company[j].complaintcount << '\n'; j++;
        } cout << '\n' << '\n'; j=0;

         i++;
}

}


void Complaints :: Counting_Data(string& input_path) {

char	COMMA_DELIMITER = static_cast<char>(',');
char	QUOTATION_DELIMITER = static_cast<char>('"');


File.open(input_path); //The input path is "./input/complaints.csv."


while (File.peek() != '\n') { field = static_cast<char>(File.get()); cout << field; }

position = 0;
while ( !File.eof() ) {

	field = static_cast<char>(File.get());

		if 			( field == COMMA_DELIMITER  )   					                    { position++; }
		if  	   	( field == '\n' )														{ position = 0;}
        if          ( File.peek() == char_traits<char>::eof() )   							{ cout << '\n' << "Finished\n"; break; }

        if (position == date_column)
		{	date_name.clear();
			while (position < (date_column+1)) {
				field = static_cast<char>(File.get());
                if			( field == COMMA_DELIMITER )						            {position++; if (date_name == "" || date_name ==" ") {date_name="Blank";}}
				else if		( ispunct(field) )												{date_name += string(1,field);}
				else if     ( isdigit(field) )												{date_name += string(1,field);}
				else if     ( isalpha(field) )												{date_name += string(1,field);}
                else                                                                        {position++;}
			}
		}


		if (position == product_column)
		{	product_name.clear();
			while (position < (product_column+1)) {
				ofield = static_cast<char>(File.get()); field = tolower(ofield);
                if			( field == COMMA_DELIMITER && isalpha(File.peek()) )		{position++; if (product_name == "" || product_name == " ") {product_name="Blank";}}
				else if		( ispunct(field) )											{product_name += string(1,field);}
				else if     ( isalpha(field) )											{product_name += string(1,field);}
				else if     ( isspace(field) )											{product_name += string(1,field);}

			}
		}

		if (position == company_column)
		{	company_name.clear();
			while (position < (company_column+1)) {
				ofield = static_cast<char>(File.get()); field = toupper(ofield);
				if 	( field == QUOTATION_DELIMITER && File.peek() == COMMA_DELIMITER)   {position++; company_name += string(1,field);if (company_name == "" || company_name == " ") {company_name="Blank";}}
				else if 	( field == COMMA_DELIMITER && isalpha(File.peek()) )		{position++; if (company_name == "") {company_name="Blank";}}
				else if	    ( ispunct(field) )											{company_name += string(1,field);}
				else if     ( isalpha(field) )											{company_name += string(1,field);}
				else if     ( isspace(field) )											{company_name += string(1,field);}
				}
		}


		part_date_name = date_name.substr(0,4);

		if ( part_date_name == "2018" && File.peek() == '\n' )
		{	part_date_name.clear();
			i=0;
			while (i < FY18.product.size()) {
				if (FY18.product[i].name.compare(product_name) == 0)
				{  FY18.product[i].productcount++;
					j=0;
					while (j < FY18.product[i].company.size()){
						if (FY18.product[i].company[j].name.compare(company_name) == 0)
						{	FY18.product[i].company[j].complaintcount++;
						} j++;
					}
				} i++;
			}
		}


		if ( part_date_name == "2019" && File.peek() == '\n' )
		{	part_date_name.clear();
			i=0;
			while (i < FY19.product.size()) {
				if (FY19.product[i].name.compare(product_name) == 0)
				{ FY19.product[i].productcount++;
					j=0;
					while (j < FY19.product[i].company.size()){
						if (FY19.product[i].company[j].name.compare(company_name) == 0)
						{	FY19.product[i].company[j].complaintcount++; //cout << company_name << '\t' << FY19.product[i].company[j].name << '\n';
						} j++;
					}
				} i++;
			}
		}


		if ( part_date_name == "2020" && File.peek() == '\n')
		{	part_date_name.clear();
			i=0;
			while (i < FY20.product.size()) {
				if (FY20.product[i].name.compare(product_name) == 0)
				{  FY20.product[i].productcount++; cout << '\t' << FY20.product[i].productcount << '\n';
					j=0;
					while (j < FY20.product[i].company.size()){
						if (FY20.product[i].company[j].name.compare(company_name) == 0)
						{	FY20.product[i].company[j].complaintcount++;
						} j++;
					}
				} i++;
			}
		}

	}

File.close();

}


void Complaints :: Output_Data (string& output_path) {

New_File.open(output_path); // The output path is "./output/report.csv."
cout.precision(0);

int maximum, result, sum, sum_companies;


for (i=0; i < FY18.product.size(); i++) {
	j=0; maximum, result, sum, sum_companies = 0;
	while (j < FY18.product[i].company.size()) {
	product_complaintcount.push_back(FY18.product[i].company[j].complaintcount);
	j++;
	}

	maximum = *max_element(product_complaintcount.begin(), product_complaintcount.end());
	sum = accumulate(product_complaintcount.begin(), product_complaintcount.end(), 0);
	sum_companies = ( product_complaintcount.size() -  count(product_complaintcount.begin(), product_complaintcount.end(), 0) );

	New_File << FY18.product[i].name << ",";
	New_File << FY18.year << ",";
	New_File << sum << ",";
	New_File << sum_companies << ",";

	if (sum == 0)	{New_File << 0 << '\n';}
	else {  result = 100 * ( maximum / static_cast<float>(sum) );
			New_File <<  std::setprecision(2) << result << '\n'; }

	product_complaintcount.clear();

	}


for (i=0; i < FY19.product.size(); i++) {
	j=0; maximum, result, sum, sum_companies = 0;
	while (j < FY19.product[i].company.size()) {
	product_complaintcount.push_back(FY19.product[i].company[j].complaintcount);
	j++;
	}

	maximum = *max_element(product_complaintcount.begin(), product_complaintcount.end());
	sum = accumulate(product_complaintcount.begin(), product_complaintcount.end(), 0);
	sum_companies = ( product_complaintcount.size() -  count(product_complaintcount.begin(), product_complaintcount.end(), 0) );

	New_File << FY19.product[i].name << ",";
	New_File << FY19.year << ",";
	New_File << sum << ",";
	New_File << sum_companies << ",";

	if (sum == 0)	{New_File << 0 << '\n';}
	else {  result = 100 * ( maximum / static_cast<float>(sum) );
			New_File <<  std::setprecision(2) << result << '\n'; }

	product_complaintcount.clear();

	}



for (i=0; i < FY20.product.size(); i++) {
	j=0; maximum, result, sum, sum_companies = 0;
	while (j < FY20.product[i].company.size()) {
	product_complaintcount.push_back(FY19.product[i].company[j].complaintcount);
	j++;
	}

	maximum = *max_element(product_complaintcount.begin(), product_complaintcount.end());
	sum = accumulate(product_complaintcount.begin(), product_complaintcount.end(), 0);
	sum_companies = ( product_complaintcount.size() -  count(product_complaintcount.begin(), product_complaintcount.end(), 0) );

     cout << '\n';
	 cout << '\n' << '\n' << "Product Name\t" << FY20.product[i].name;
	 cout << '\n' << '\n' << "Year\t" << FY20.year << '\n' << '\n';
	 cout << "product_complaintcount\t" << accumulate(product_complaintcount.begin(), product_complaintcount.end(), 0);
	 cout << '\n' << '\n' << "max_element\t" << *max_element(product_complaintcount.begin(), product_complaintcount.end());
	 cout << '\n' << '\n' << "sum_companies\t" << sum_companies;

	if (sum == 0)	{cout << '\n' << '\n' << "percentage of product_complaintcount\t" << "NA\n" << '\n';}
	else {  cout << '\n' << '\n' << "percentage of product_complaintcount\t";
		    result = 100 * ( maximum / static_cast<float>(sum) );
			cout <<  std::setprecision(2) << result ; }

	New_File << FY20.product[i].name << ",";
	New_File << FY20.year << ",";
	New_File << sum << ",";
	New_File << sum_companies << ",";

	if (sum == 0)	{New_File << 0 << '\n';}
	else {  result = 100 * ( maximum / static_cast<float>(sum) );
			New_File <<  std::setprecision(2) << result << '\n'; }

	 product_complaintcount.clear();

	}

cout << '\n';

New_File.close();
}
