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
Years 				FY10, FY11, FY12, FY13, FY14, FY15, FY16, FY17, FY18, FY19, FY20;
string				header_column, company_name, date_name, part_date_name, product_name;
vector<int> 		product_complaintcount;
vector<string> 		header, header_names, company_set, product_set;
vector<string>::iterator    CP;
};



int main ( char* argv[] ) {


string INPUT_PATH = argv[0]
string OUTPUT_PATH = arg[1]


//Declaring the Data Object
Complaints ConsumerComplaints;

//Declaring Header Names to Find
vector<string>		various_header_names;
various_header_names.push_back("Date received");
various_header_names.push_back("Product");
various_header_names.push_back("Company");


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


cout << '\n' << "Header Column Names\n";

while (File.peek() != '\n') {

field = static_cast<char>(File.get());
cout << field;

if 		(field == COMMA_DELIMITER) 	{header.push_back(header_column); header_column.clear(); }
else if ( File.peek() == '\n' )		{header_column += string(1,field), header.push_back(header_column), header_column.clear();}
else								{header_column += string(1,field);}
}


cout << '\n' << '\n' << "Columns of Respective Header Names";

i = 0;
while (i < header.size()) {
if (header[i].compare(header_names.at(0)) == 0)		{date_column = i;}
i++;
}

cout << '\n' << '\n' << "Date column\t" << date_column;

i = 0;
while (i < header.size()) {
if (header[i].compare(header_names.at(1)) == 0)		{product_column = i;}
i++;
}

cout << '\n' << "Product column\t" << product_column;

i = 0;
while (i < header.size()) {
if (header[i].compare(header_names.at(2)) == 0)		{company_column = i;}
i++;
}

cout << '\n' << "Company column\t" << company_column;


position = 0;
while ( !File.eof() ) {

	field = static_cast<char>(File.get());

		if 			( field == COMMA_DELIMITER  )   					                    { position++; }
		if  	   	( field == '\n' )														{ position = 0; }
        if          ( File.peek() == char_traits<char>::eof() )   							{ break; }


		if (position == product_column)
		{	while (position < (product_column+1)) {
				ofield = static_cast<char>(File.get()); field = tolower(ofield);
                if			( field == COMMA_DELIMITER && isalpha(File.peek()) )			{position++;
                            if (product_name.length() > 78)                 { product_name = "verbose, misentered response"; product_set.push_back(product_name); product_name.clear();}
                            else if (product_name=="" || product_name==" ") { product_name = "blank"; product_set.push_back(product_name); product_name.clear(); }
                            else if (ispunct(product_name[0]) && product_name.length()< 1 )                 { product_name = "blank"; product_set.push_back(product_name); product_name.clear(); }
                            else                                            { product_set.push_back(product_name); product_name.clear();} }
				else if		( ispunct(field) )													{product_name += string(1,field);}
				else if     ( isalpha(field) )													{product_name += string(1,field);}
				else if     ( isspace(field) )													{product_name += string(1,field);}

			}
		}


		if (position == company_column)
		{	while (position < (company_column+1)) {
				ofield = static_cast<char>(File.get()); field = toupper(ofield);
				if 	( field == QUOTATION_DELIMITER && File.peek() == COMMA_DELIMITER)       {position++; company_name += string(1,field);
                            if (company_name.length() > 50)                     { company_name = "verbose, misentered response"; company_set.push_back(company_name); company_name.clear();}
                            else if (company_name == "" || company_name == " ") { company_name = "blank"; company_set.push_back(company_name); company_name.clear();}
                            else if (ispunct(company_name.at(0)) && company_name.length() < 1)                     { company_name = "blank"; company_set.push_back(company_name); company_name.clear();}
                            else                          { company_set.push_back(company_name); company_name.clear();} }
				else if 	( field == COMMA_DELIMITER && isalpha(File.peek()) )				{position++;
                            if (company_name.length() > 50)                     { company_name = "verbose, misentered response"; company_set.push_back(company_name); company_name.clear();}
                            else if (company_name == "" || company_name == " ") { company_name = "blank"; company_set.push_back(company_name); company_name.clear();}
                            else if (ispunct(company_name.at(0)) && company_name.length() < 1)                     { company_name = "blank"; company_set.push_back(company_name); company_name.clear();}
                            else                                                { company_set.push_back(company_name); company_name.clear();} }
				else if	    ( ispunct(field) )													{company_name += string(1,field);}
				else if     ( isalpha(field) )													{company_name += string(1,field);}
				else if     ( isspace(field) )													{company_name += string(1,field);}
				}
		}

}

File.close();

}


void Complaints :: Filing_Data() {

CP = unique(company_set.begin(), company_set.end());
company_set.resize( distance(company_set.begin(),CP) );
sort(company_set.begin(), company_set.end());

CP = unique(product_set.begin(), product_set.end());
product_set.resize( distance(product_set.begin(),CP) );
sort(product_set.begin(), product_set.end());

cout << '\n' << '\n';
i=100; cout << '\n' << "After Sorting: product_set.size\t" << product_set.size() << '\n' << '\n';
while (i++ < 110) {cout << '\n' << product_set.at(i);}

cout << '\n' << '\n';
i=100; cout << '\n' << "After Sorting: company_set.size\t" << company_set.size() << '\n' << '\n';
while (i++ < 110) {cout << '\n' << company_set.at(i);}


i=0; j=0;
FY10.product.reserve(product_set.size());
FY11.product.reserve(product_set.size());
FY12.product.reserve(product_set.size());
FY13.product.reserve(product_set.size());
FY14.product.reserve(product_set.size());
FY15.product.reserve(product_set.size());
FY16.product.reserve(product_set.size());
FY17.product.reserve(product_set.size());
FY18.product.reserve(product_set.size());
FY19.product.reserve(product_set.size());
FY20.product.reserve(product_set.size());
while (i < product_set.size()) {
	ConsumerProduct.name = product_set[i++];
	ConsumerProduct.productcount = 0;

    ConsumerProduct.company.reserve(company_set.size());
	while (j < company_set.size()) {
	Corporation.name = company_set[j++];
	Corporation.complaintcount = 0;
	ConsumerProduct.company.push_back(Corporation);
	} j=0;

	FY10.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY10.year = "2010";

	FY11.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY11.year = "2011";

	FY12.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY12.year = "2012";

	FY13.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY13.year = "2013";

	FY14.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY14.year = "2014";

	FY15.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY15.year = "2015";

	FY16.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY16.year = "2016";

	FY17.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY17.year = "2017";

	FY18.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY18.year = "2018";

	FY19.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY19.year = "2019";

	FY20.product.push_back(ConsumerProduct);
	ConsumerProduct.company.clear();
	FY20.year = "2020";
}


}


void Complaints :: Counting_Data(string& input_path) {

char	COMMA_DELIMITER = static_cast<char>(',');
char	QUOTATION_DELIMITER = static_cast<char>('"');


File.open(input_path);


while (File.peek() != '\n') { field = static_cast<char>(File.get()); }

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
						{	FY19.product[i].company[j].complaintcount++;
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
				{  FY20.product[i].productcount++;
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

New_File.open(output_path);
cout.precision(0);

int maximum, result, sum, sum_companies;

cout << '\n' << '\n';


for (i=0; i < FY10.product.size(); i++) {
	j=0; maximum, result, sum, sum_companies = 0;
	while (j < FY10.product[i].company.size()) {
	product_complaintcount.push_back(FY10.product[i].company[j].complaintcount);
	j++;
	}

	maximum = *max_element(product_complaintcount.begin(), product_complaintcount.end());
	sum = accumulate(product_complaintcount.begin(), product_complaintcount.end(), 0);
	sum_companies = ( product_complaintcount.size() -  count(product_complaintcount.begin(), product_complaintcount.end(), 0) );
	
	New_File << FY10.product[i].name << ",";
	New_File << FY10.year << ",";
	New_File << sum << ",";
	New_File << sum_companies << ",";

	if (sum == 0)	{New_File << 0 << '\n';}
	else {  result = 100 * ( maximum / static_cast<float>(sum) );
			New_File <<  std::setprecision(2) << result << '\n'; }
    
	product_complaintcount.clear();

	}


for (i=0; i < FY11.product.size(); i++) {
	j=0; maximum, result, sum, sum_companies = 0;
	while (j < FY11.product[i].company.size()) {
	product_complaintcount.push_back(FY11.product[i].company[j].complaintcount);
	j++;
	}

	maximum = *max_element(product_complaintcount.begin(), product_complaintcount.end());
	sum = accumulate(product_complaintcount.begin(), product_complaintcount.end(), 0);
	sum_companies = ( product_complaintcount.size() -  count(product_complaintcount.begin(), product_complaintcount.end(), 0) );

	New_File << FY11.product[i].name << ",";
	New_File << FY11.year << ",";
	New_File << sum << ",";
	New_File << sum_companies << ",";

	if (sum == 0)	{New_File << 0 << '\n';}
	else {  result = 100 * ( maximum / static_cast<float>(sum) );
			New_File <<  std::setprecision(2) << result << '\n'; }
    
	product_complaintcount.clear();

	}


for (i=0; i < FY12.product.size(); i++) {
	j=0; maximum, result, sum, sum_companies = 0;
	while (j < FY12.product[i].company.size()) {
	product_complaintcount.push_back(FY12.product[i].company[j].complaintcount);
	j++;
	}

	maximum = *max_element(product_complaintcount.begin(), product_complaintcount.end());
	sum = accumulate(product_complaintcount.begin(), product_complaintcount.end(), 0);
	sum_companies = ( product_complaintcount.size() -  count(product_complaintcount.begin(), product_complaintcount.end(), 0) );

	New_File << FY12.product[i].name << ",";
	New_File << FY12.year << ",";
	New_File << sum << ",";
	New_File << sum_companies << ",";

	if (sum == 0)	{New_File << 0 << '\n';}
	else {  result = 100 * ( maximum / static_cast<float>(sum) );
			New_File <<  std::setprecision(2) << result << '\n'; }
    
	product_complaintcount.clear();

	}


for (i=0; i < FY13.product.size(); i++) {
	j=0; maximum, result, sum, sum_companies = 0;
	while (j < FY13.product[i].company.size()) {
	product_complaintcount.push_back(FY13.product[i].company[j].complaintcount);
	j++;
	}

	maximum = *max_element(product_complaintcount.begin(), product_complaintcount.end());
	sum = accumulate(product_complaintcount.begin(), product_complaintcount.end(), 0);
	sum_companies = ( product_complaintcount.size() -  count(product_complaintcount.begin(), product_complaintcount.end(), 0) );

	New_File << FY13.product[i].name << ",";
	New_File << FY13.year << ",";
	New_File << sum << ",";
	New_File << sum_companies << ",";

	if (sum == 0)	{New_File << 0 << '\n';}
	else {  result = 100 * ( maximum / static_cast<float>(sum) );
			New_File <<  std::setprecision(2) << result << '\n'; }
    
	product_complaintcount.clear();

	}


for (i=0; i < FY14.product.size(); i++) {
	j=0; maximum, result, sum, sum_companies = 0;
	while (j < FY14.product[i].company.size()) {
	product_complaintcount.push_back(FY14.product[i].company[j].complaintcount);
	j++;
	}

	maximum = *max_element(product_complaintcount.begin(), product_complaintcount.end());
	sum = accumulate(product_complaintcount.begin(), product_complaintcount.end(), 0);
	sum_companies = ( product_complaintcount.size() -  count(product_complaintcount.begin(), product_complaintcount.end(), 0) );

	New_File << FY14.product[i].name << ",";
	New_File << FY14.year << ",";
	New_File << sum << ",";
	New_File << sum_companies << ",";

	if (sum == 0)	{New_File << 0 << '\n';}
	else {  result = 100 * ( maximum / static_cast<float>(sum) );
			New_File <<  std::setprecision(2) << result << '\n'; }
    
	product_complaintcount.clear();

	}


for (i=0; i < FY15.product.size(); i++) {
	j=0; maximum, result, sum, sum_companies = 0;
	while (j < FY15.product[i].company.size()) {
	product_complaintcount.push_back(FY15.product[i].company[j].complaintcount);
	j++;
	}

	maximum = *max_element(product_complaintcount.begin(), product_complaintcount.end());
	sum = accumulate(product_complaintcount.begin(), product_complaintcount.end(), 0);
	sum_companies = ( product_complaintcount.size() -  count(product_complaintcount.begin(), product_complaintcount.end(), 0) );

	New_File << FY15.product[i].name << ",";
	New_File << FY15.year << ",";
	New_File << sum << ",";
	New_File << sum_companies << ",";

	if (sum == 0)	{New_File << 0 << '\n';}
	else {  result = 100 * ( maximum / static_cast<float>(sum) );
			New_File <<  std::setprecision(2) << result << '\n'; }
    
	product_complaintcount.clear();

	}


for (i=0; i < FY16.product.size(); i++) {
	j=0; maximum, result, sum, sum_companies = 0;
	while (j < FY16.product[i].company.size()) {
	product_complaintcount.push_back(FY16.product[i].company[j].complaintcount);
	j++;
	}

	maximum = *max_element(product_complaintcount.begin(), product_complaintcount.end());
	sum = accumulate(product_complaintcount.begin(), product_complaintcount.end(), 0);
	sum_companies = ( product_complaintcount.size() -  count(product_complaintcount.begin(), product_complaintcount.end(), 0) );

	New_File << FY16.product[i].name << ",";
	New_File << FY16.year << ",";
	New_File << sum << ",";
	New_File << sum_companies << ",";

	if (sum == 0)	{New_File << 0 << '\n';}
	else {  result = 100 * ( maximum / static_cast<float>(sum) );
			New_File <<  std::setprecision(2) << result << '\n'; }
    
	product_complaintcount.clear();

	}


for (i=0; i < FY17.product.size(); i++) {
	j=0; maximum, result, sum, sum_companies = 0;
	while (j < FY17.product[i].company.size()) {
	product_complaintcount.push_back(FY17.product[i].company[j].complaintcount);
	j++;
	}

	maximum = *max_element(product_complaintcount.begin(), product_complaintcount.end());
	sum = accumulate(product_complaintcount.begin(), product_complaintcount.end(), 0);
	sum_companies = ( product_complaintcount.size() -  count(product_complaintcount.begin(), product_complaintcount.end(), 0) );

	New_File << FY17.product[i].name << ",";
	New_File << FY17.year << ",";
	New_File << sum << ",";
	New_File << sum_companies << ",";

	if (sum == 0)	{New_File << 0 << '\n';}
	else {  result = 100 * ( maximum / static_cast<float>(sum) );
			New_File <<  std::setprecision(2) << result << '\n'; }
    
	product_complaintcount.clear();

	}



for (i=0; i < 18; i++) {
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
