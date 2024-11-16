
#include "Manager.h"
#include "iostream"
#include "string"

Manager::Manager() {};
Manager::~Manager() {};


void Manager::run(const char* command)
{
    string cmd; // save line
    string other; // save index
    // Open command & log file
    fcmd.open(command); // read files 
    flog.open("log.txt");// write data files
    if (!fcmd) // if file doesn't exist
    {
        flog << "Fail to open command file" << endl; // write error
        exit(-1);
    }

    // Run command
    while (getline(fcmd, line)) { // just cmd or  cmd with inedx
        if (line.find(' ') != std::string::npos) { // index exist
            cmd = line.substr(0,line.find(' ')); // read cmd
            other = line.substr(line.find(' ') + 1, line.find('\0')); // read index
          
            if (cmd == "ADD") { // cmd add
                ADD(other);
            }
            else if (cmd == "SEARCH") { // cmd search
                SEARCH(other);
            }
            else if (cmd=="PRINT") { // cmd print
                PRINT(other);
            }
            else if(cmd=="DELETE") { // cmd delete
             DELETE(other);
            }
            else {
                flog << "1000" << endl; // the other input
            }
        }
        else {// 단일 명령어
            cmd = line;
            if (cmd == "LOAD") { // load cmd
               LOAD("data.txt");
            }
            else if (cmd == "QPOP") { // qpop cmd
                QPOP();
            }
            else if (cmd=="EXIT") { // exit cmd
                EXIT();
            }
            else {
                flog << "1000" << endl; // other cmd
            }
        }


    
    }


    fcmd.close(); // file close
    flog.close(); // cile close
    return;
}

void Manager::PrintSuccess(const char* cmd)// when cmd success
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}
void Manager::PrintErrorCode(int num) // print error code
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl << endl;
}


void Manager::LOAD(const char* data_files) { // get data for txt
    fdata.open(data_files); // file open
    if (!fcmd) // file doesn't exit
    {
        flog << "Fail to open data file" << endl; //print error message
        exit(-1);
    }
    // Load Files 
    if (m_Queue.empty() == 0) { // aready data exist
        PrintErrorCode(100); // error
        return;
    }

    flog << "===== LOAD =====" << endl; //print

    while (getline(fdata, line_data)) { // end of line
       m_Queue.push(line_data); //analyze line save Q
       flog << m_Queue.rear().getname()<<"/"//print
               << m_Queue.rear().getage()<<"/"//print
               << m_Queue.rear().getdate()<<"/"//print
               << m_Queue.rear().gettype()//print
               <<endl;
    }
    flog << "================" << endl; //message print
  
}


void Manager::ADD(string line) { // new data add
    int i=0;
    if (line.find(" ",i) > 20) {// name wrong
        PrintErrorCode(200);//error
        return;
    }
    i = line.find(" ", i)+1;
    if (line.find(" ", i) > i+2) {//age wrong
        PrintErrorCode(200);//error
        return;
    }
    i = line.find(" ", i)+1;
    if (line.find(" ", i) != i+10) {// date wrong
        PrintErrorCode(200);//
        return;
    }
    i = line.find(" ", i)+1;
    if (line.find("\0", i) !=i ) {//type wrong
        PrintErrorCode(200);//
        return;
    }

    if (m_Queue.push(line)==0) { // no data
        PrintErrorCode(200);//
        return;
    }
    flog << "===== ADD =====" << endl; // add
    flog << m_Queue.rear().getname() << "/"//
        << m_Queue.rear().getage() << "/"//
        << m_Queue.rear().getdate() << "/"//
        << m_Queue.rear().gettype()//   
        << endl;
   flog << "===============" << endl; // 
}

bool Manager::QPOP() { 
    if (m_Queue.pop(&t_list, &N_bst) == 0) { //Q is empty
        PrintErrorCode(300); // 
        exit(-1);// end program
    }
    PrintSuccess("QPOP"); // is sucesss
};

    void Manager::SEARCH(string name) {
        NameBSTNode* temp = N_bst.search(name); // search by name

        if (temp == nullptr) {
            PrintErrorCode(400); // error
        }

       flog << "========SEARCH=======" << endl; // print
    flog << temp->getname() <<"/"<<temp->getage()<<"/" << temp->getstartdate()
            <<"/"<< temp->getenddate() << endl; // print
    flog << "=====================" << endl; // print
    return;
    }

    void Manager::PRINT(string input) {
        if (N_bst.getRoot() == nullptr) { // no name
            PrintErrorCode(500); // error 
        }
        if (input == "NAME") { // get name
        flog << "===== PRINT =====" << endl;
        flog << "Name_BST" << endl;
        N_bst.print(N_bst.getRoot(), &flog); // result print
        flog << "================" << endl;
        return;
        }
        else {//
            if (t_list.search(input) == nullptr) { // no type
                PrintErrorCode(500); // error
                return;
           }
            flog << "===== PRINT =====" << endl;
            flog << "Terms_BST" << endl;
            t_list.search(input)->gettermbst()->print(t_list.search(input)->gettermbst()->getRoot(), &flog);
            //print by type
            flog << "================" << endl;
            return;
        }
}
  
    void  Manager ::DELETE(string data){ //delete
        string cmd = data.substr(0,data.find(' '));
        string obj = data.substr(data.find(' ')+1, data.find('\0'));
        if (t_list.getHead() == nullptr) {
            PrintErrorCode(600); // error
            return;
        }
        
        if (cmd =="DATE") {//get date
            t_list.delete_list(obj, &N_bst); // delete
        }
        else if(cmd=="NAME") { //get name
            if (N_bst.search(obj) == nullptr) {
                PrintErrorCode(600); // error
                return;
            }
            char type= N_bst.search(obj)->gettype(); //search name
            string enddate= N_bst.search(obj)->getenddate();//enddate upload
            N_bst.delete_name(obj); // delete n_bst
            t_list.delete_list_name(obj, type, enddate);//delete tlistand tbst
        }
        PrintSuccess("DELETE"); // // print
       
    }

void Manager::EXIT() { // end program

    PrintSuccess("EXIT");
    exit(-1);

}