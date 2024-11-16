#include "Manager.h"

void Manager::run(const char* command)
{

	fin.open(command);
	flog.open("log.txt");// write data files
	if (!fin)
	{
		flog << "File Open Error" << endl;// errorcode
		return; // program end
	}
	while (!fin.eof())
	{
		while (getline(fin, line)) {
			s = 0; // intger to divdie command
			while (line[s] != '\t'&&line[s]!=NULL) // end of line or to meet tab stop
				s++;
			cmd = line.substr(0, s); // cut command
			s++;
			if (cmd.compare("LOAD") == 0) {
				if (LOAD() == false) // start load
					printErrorCode(100);
			}
			else if (cmd.compare("ADD") == 0) {
				if (ADD() == false) // start add
					printErrorCode(200); // print error
			}
			else if (cmd.compare("SEARCH_BP") == 0) {
				cmd = '\0'; // cmd reset
				cmd = line.substr(s, line.length()); // get data
				if (cmd.length() == 3) {
					if (cmd[1] == '\t') {//if it is range
						if(SEARCH_BP_RANGE(cmd.substr(0, 1), cmd.substr(2, 1))==false)
							printErrorCode(300);
					}
					else {
						if (SEARCH_BP_BOOK(cmd) == false); // if it is name data
						printErrorCode(300);
					}
				}
				else {
					if(SEARCH_BP_BOOK(cmd)==false)// if it is name data
					printErrorCode(300);
				}
			}// end of search bp tree
			else if (cmd.compare("PRINT_BP") == 0) {

				if (PRINT_BP() == false) // print b+ tree
				{
					printErrorCode(400);
				};
			}
			else if (cmd.compare("PRINT_ST") == 0) {
				if (PRINT_ST() == false)// print seletion tree 
					printErrorCode(500);
			}
			else if (cmd.compare("DELETE") == 0) {
				if (DELETE() == false) // delete  seletion tree root
					printErrorCode(600);
			}
			else if (cmd.compare("EXIT") == 0) {
	
				return; // end 
			}
			else {
				printErrorCode(700);
			}
		}
	}
	fin.close();
	return;

}



bool Manager::LOAD()
{
	string m_name; // name data
	int m_code;// code data
	string m_author;// author data
	int m_year;// year data
	int s; 
	floan_book.open("loan_book.txt");

	if (!floan_book.is_open() || bptree->getRoot() != NULL) { // no file or already exist data
		return false;
	}
	
	while (getline(floan_book, book_data)) {
		s = 0;
		while (book_data[s] != '\t')// divde by tab
			s++;

		m_name = book_data.substr(0, s); // get  name
		s++;
		m_code = stoi(book_data.substr(s, 3));// get code and save integer
		s += 4;
		m_author = book_data.substr(s, (book_data.length() - 7 - s)); // save author
		m_year = stoi(book_data.substr(book_data.length() - 6, 4));// save years
		LoanBookData* temp; // make new data
		temp = new LoanBookData;
		temp->setBookData(m_name, m_code, m_author, m_year); // make loan book data

	
		bptree->Insert(temp); // add in tree


	}
	flog << "========LOAD========" << endl;
	flog << "SUCCESS" << endl;
	flog << "====================" << endl;
	return true;

}

bool Manager::ADD()
{
	line = line.substr(s, line.length()); // read line
	int countr = count(line.begin(), line.end(), '\t'); // data is 4
	if (countr != 3) { // if not error
		return false;
	}
	/*same to read data load*/
	string name;
	int code;
	string author;	
	int year;
	int s = 0;
	while (line[s] != '\t')
		s++;
	name = line.substr(0, s); 
	s++;
	code = stoi(line.substr(s, 3));
	s += 4;
	author = line.substr(s, (line.length() - 5 - s));
	year = stoi(line.substr(line.length() - 4, 4));
	// if it  is not exist
	if (bptree->searchDataNode(name)->getDataMap()->find(name) == bptree->searchDataNode(name)->getDataMap()->end()){
		LoanBookData* temp; 
		temp = new LoanBookData;
		temp->setBookData(name, code, author, year); // new data
		bptree->Insert(temp); // add tree 
	}
	else {
		bptree->searchDataNode(name)->getDataMap()->find(name)->second->updateCount();
		///delete  condition
		int count = bptree->searchDataNode(name)->getDataMap()->find(name)->second->getLoanCount(); // get count 
		switch (code) {
		case 0:
		case 100:
		case 200:
			if(count==3){
				// data move to ST tree
				stree->Insert(bptree->searchDataNode(name)->getDataMap()->find(name)->second);
				bptree->deletenode(name);
				
			}
			break;
		case 300:
		case 400:
			if(count==4){
				// data move to ST tree
				stree->Insert(bptree->searchDataNode(name)->getDataMap()->find(name)->second);
				//bptree->deletenode(name);

			}
			break;
		case 500:
		case 600:
		case 700:
			if(count==2){
				// data move to ST tree
				stree->Insert(bptree->searchDataNode(name)->getDataMap()->find(name)->second);
			//	bptree->deletenode(name);
			}
			break;
		default:
			
			break;
		}

	}
	flog << "========ADD========" << endl;
	flog << name << "/" << code << "/" << author << "/" << year << endl;
	flog << "====================" << endl;
}

bool Manager::SEARCH_BP_BOOK(string book) 
{
	LoanBookData* temp;
	if (bptree->searchBook(book) == true) {//if thebok exit
		flog << "========SEARCH_BP========" << endl;
		temp = bptree->searchDataNode(book)->getDataMap()->find(book)->second;
		flog << temp->getName() <<"/" << temp->getCode() << "/" << temp->getAuthor() << "/" << temp->getYear()<<"/" <<temp->getLoanCount()<<endl;
		flog<< "========================" << endl;
		//print book data
		return true;
	}
	else
		return false;// not exist

}

bool Manager::SEARCH_BP_RANGE(string s, string e) 
{
	if (bptree->searchRange(s, e, &flog) == false) // BP range print
		return false;


	return true;
}

bool Manager::PRINT_BP() 
{
	
	return bptree->print(); // print bp

}

bool Manager::PRINT_ST()
{
	line = line.substr(s, line.length());
	int code = stoi(line); // get code
	if (code != 0 && code != 100 && code != 200 && code != 300 && code != 400 && code != 500 && code != 600 && code != 700)
	{
		return false;
}
	
	if (stree->printBookData(code) == false) { // find data
		return false;
	}
	return true;
}

bool Manager::DELETE() 
{

	if (stree->Delete() == false)
		return false;
	else
	flog << "========DELETE========" << endl;
	flog << "                     Success                " << endl;
	flog << "=======================" << endl;
	return true;
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "=======================" << endl;
	flog << "ERROR " << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
	flog << "=======================" << endl;
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}

void Manager::BP_DELETE(string name) { // bp tree delete
		bptree->deletenode(name);
}

