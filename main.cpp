//Jake Weintroub cs 141 Project 4: Red Light Cameras
// This Project analyzes data provided by Red Light Cameras in Chicago 
// The Code does 4 things
// A data overview, Results by neighborhood, A monthly chart, and a search for cameras 
// These are explained by their functions 
// Oh lets break it down!!

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class CameraRecord { //a class that stores all the data for each camera
    public:
        CameraRecord(string fileinter, string fileaddy, int fileCamno, string filedate, int fileNOV, string filehood);
        void testprint();
        string getintersection();
        string getaddress();
        int getCameraNumber();
        string getdate();
        int getNoOfVios();
        string getneighborhood();
    private:
        string intersection;
        string address;
        int CameraNumber;
        string date;
        int NoOfVios;
        string neighborhood;

};

CameraRecord::CameraRecord(string fileinter, string fileaddy, int fileCamno, string filedate, int fileNOV, string filehood) { // constructer used to initalize cameras
    intersection=fileinter;
    address=fileaddy;
    CameraNumber=fileCamno;
    date=filedate;
    NoOfVios=fileNOV;
    neighborhood=filehood;
}
string CameraRecord::getintersection() { // these are all get functions very simple
    return intersection;
}

string CameraRecord::getaddress() {
    return address;
}

string CameraRecord::getdate() {
    return date;
}

string CameraRecord::getneighborhood() {
    return neighborhood;
}

int CameraRecord::getNoOfVios() {
    return NoOfVios;
}

int CameraRecord::getCameraNumber() {
    return CameraNumber;
}

void CameraRecord::testprint() { // i used this to make sure everything worked before making the functions
    cout << intersection << endl;
    cout << address << endl;
    cout << CameraNumber << endl;
    cout << date << endl;
    cout << NoOfVios << endl;
    cout << neighborhood << endl;
}

void ReadFile(string fileName, vector<CameraRecord>& Records, vector<string>& neighborhoodlist) { // how i set up each camera in the class and read data from the file
    string fileinter, fileaddy, fileCamnostr, filedate, fileNOVstr, filehood; //these are new varibles made for the sole purpose of collecting the data from the file. they are all strings and the two that need to be ints will be converted
    int fileCamno, fileNOV;
    
    ifstream fileIn;
    fileIn.open(fileName);
    //while file is not at its end it takes in the line and creates a object for it
    while (!fileIn.eof()) {
        if (fileIn.eof()) {
            break;
        }
        getline(fileIn, fileinter, ',');
        getline(fileIn, fileaddy, ',');
        getline(fileIn, fileCamnostr, ',');
        fileCamno=stoi(fileCamnostr);
        getline(fileIn, filedate, ',');
        getline(fileIn, fileNOVstr, ',');
        fileNOV=stoi(fileNOVstr);
        getline(fileIn, filehood);
        
        CameraRecord filerecord(fileinter,fileaddy,fileCamno,filedate,fileNOV,filehood); // adding every camera into a vector used to store everything
        Records.push_back(filerecord);
    }
    int vecsize=Records.size();
    int listsize=neighborhoodlist.size();
    bool canadd=true;
    for (int i=0; i<vecsize; i++) { // creates a vector of neighberhoods bool is used to see if neighberhood in the vector
        canadd=true;
        for (int j=0; j<listsize; j++) {
            if(neighborhoodlist[j]==Records[i].getneighborhood()) {
                canadd=false;
                break;
            }
        }
        if (canadd==true) {
        neighborhoodlist.push_back(Records[i].getneighborhood());
        listsize+=1;
        }
    }
}

string formatdate(string& date) { // used to change the date format the way the autograder liked it
    string y;
    string m;
    string d;
    int j=0;
    int strlng=date.length();
    for (int i=0; i<strlng; i++) { // interates through all charecters in the date and changes the order
        char ch = date[i];
        if (ch == '-') {
            j++;
        }
        else {
            if (j==0) {
                y+=ch;
            }
            else if (j==1) {
                m+=ch;
            }
            else if (j==2) {
                d+=ch;
            }
        }
    }
    return m+'-'+d+'-'+y;
}
string findmonth(const string& date) { // rather than write an entirely new function to find the month i used my format date one and just returned the month (yes there is extra code here then) the function only worked when i made it const
        string y;
    string m;
    string d;
    int j=0;
    int strlng=date.length();
    for (int i=0; i<strlng; i++) {
        char ch = date[i];
        if (ch == '-') {
            j++;
        }
        else {
            if (j==0) {
                y+=ch;
            }
            else if (j==1) {
                m+=ch;
            }
            else if (j==2) {
                d+=ch;
            }
        }
    }
    return m;
}
void DataOverview(vector<CameraRecord>& Records) { // for the data Data overview task
    int totalrecords=Records.size();
    cout << "Read file with " << totalrecords << " records." << endl;
    vector<int> numCams;
    bool canadd = true;
    int csize=numCams.size();
    int totalvios=0;
    int viosmax=0;
    string maxviosdate;
    string maxviosinter;
    for (int i=0; i<totalrecords; i++) {//this is a little messy a bool is used to see if i have already added that camera to the count
        int camid = Records[i].getCameraNumber();
        csize=numCams.size();
        canadd=true;
        int vios=Records[i].getNoOfVios();
        totalvios+=vios;
        if (vios>viosmax) {//checking to find max
            viosmax=vios;
            maxviosinter=Records[i].getintersection();
            maxviosdate=Records[i].getdate();
        }
        for (int j=0; j<csize; j++) {
            if(numCams[j]==camid) {
            canadd=false;
            break;
            }
        }
        if (canadd==true) {
            numCams.push_back(camid);
            
        }
        csize=numCams.size();
    }
    cout << "There are " << csize << " cameras." << endl;
    cout << "A total of " << totalvios << " violations." << endl;
    cout << "The most violations in one day were " << viosmax << " on " << formatdate(maxviosdate) << " at " << maxviosinter << endl;
}
int findnumcamerasinhood(vector<CameraRecord>& Records, string& neighborhoodlist) { // for the results by neighberhood
    int recsize=Records.size();
    vector<int> camnums;
    int numsize=0;
    bool canadd = true; // again a bool used to see if a camera is already in a vector. I use this same principle throught the project
        for (int j=0; j<recsize; j++) {
            canadd=true;
            if (neighborhoodlist==Records[j].getneighborhood()) {
                for (int k=0; k<numsize; k++) {
                    if (camnums[k]==Records[j].getCameraNumber()) {
                        canadd=false;
                        break;
                    }
                }
                if (canadd==true) {
                    camnums.push_back(Records[j].getCameraNumber());
                    numsize+=1;
                }
            }
        }
        return numsize;
}
void ResultsbyHood(vector<CameraRecord>& Records, vector<string>& neighborhoodlist) { // the main results by neighberhood function
    //sort(neighborhoodlist.begin(), neighborhoodlist.end());
    int size=neighborhoodlist.size();
    int recsize=Records.size();
    vector<int> hoodvios;


    for (int i=0; i<size; i++) { //finding total violations
        int numvioshood=0;
        for (int j=0; j<recsize; j++) {
            if(neighborhoodlist[i]==Records[j].getneighborhood()) {
                numvioshood=numvioshood+Records[j].getNoOfVios();
            }
        }
        hoodvios.push_back(numvioshood);
    }
        for (int i=0; i<size-1; i++) {
            for (int j=i+1; j<size; j++) { //used to sort to look how it needed to. I belive there may have been a better way but this worked
                if (hoodvios[i]<hoodvios[j]) {
                    int tempvios = hoodvios[i];
                    hoodvios[i]=hoodvios[j];
                    hoodvios[j]=tempvios;
                    string temphood = neighborhoodlist[i];
                    neighborhoodlist[i]=neighborhoodlist[j];
                    neighborhoodlist[j]=temphood;
                }
            }
        }
        for (int i=0; i<size; i++) {
        cout << left << setw(25) << neighborhoodlist[i] << right << setw(4) << findnumcamerasinhood(Records,neighborhoodlist[i]) << setw(7) << hoodvios[i] << endl;
    }
}
void chartbymonth(vector<CameraRecord>& Records) { // function to make the chart by month
    int months[12] = {0,0,0,0,0,0,0,0,0,0,0,0}; //array is used to track all violations by month
    int recsize=Records.size();
    for (int i=0; i<recsize; i++) {
        string numstr = findmonth(Records[i].getdate());
        int monthnum= stoi(numstr);
        months[monthnum-1]+=Records[i].getNoOfVios();//-1 needed for months to line up properly
    }
    cout << "January        "; // could not think of a way that used less code so I wrote it all out for each month. In retrospect a loop most likely could have been used.
    for (int i=0; i<(months[0]/1000); i++) {
        cout<<'*';
    }
    cout << endl;
    cout << "February       ";
    for (int i=0; i<(months[1]/1000); i++) {
        cout<<'*';
    }
    cout << endl;
    cout << "March          ";
    for (int i=0; i<(months[2]/1000); i++) {
        cout<<'*';
    }
    cout << endl;
    cout << "April          ";
    for (int i=0; i<(months[3]/1000); i++) {
        cout<<'*';
    }
    cout << endl;
    cout << "May            ";
    for (int i=0; i<(months[4]/1000); i++) {
        cout<<'*';
    }
    cout << endl;
    cout << "June           ";
    for (int i=0; i<(months[5]/1000); i++) {
        cout<<'*';
    }
    cout << endl;
    cout << "July           ";
    for (int i=0; i<(months[6]/1000); i++) {
        cout<<'*';
    }
    cout << endl;
    cout << "August         ";
    for (int i=0; i<(months[7]/1000); i++) {
        cout<<'*';
    }
    cout << endl;
    cout << "September      ";
    for (int i=0; i<(months[8]/1000); i++) {
        cout<<'*';
    }
    cout << endl;
    cout << "October        ";
    for (int i=0; i<(months[9]/1000); i++) {
        cout<<'*';
    }
    cout << endl;
    cout << "November       ";
    for (int i=0; i<(months[10]/1000); i++) {
        cout<<'*';
    }
    cout << endl;
    cout << "December       ";
    for (int i=0; i<(months[11]/1000); i++) {
        cout<<'*';
    }
    cout << endl;
}
string strtolower(const string& hood) { //used to standardize input for search for cams function
    string newstr="";
    int strsize=hood.size();
    for (int i=0; i<strsize;i++) {
        newstr+=tolower(hood[i]);
    }
    return newstr;
}
void searchforcams(vector<CameraRecord>& Records, string& hood) { // main functions for seach for cams
    int recsize=Records.size();
    string newstr=strtolower(hood);
    bool anycams=false; // bool used in case of no cameras found
    bool camnotinlist=true; // again bool used to check if camera in vector or not
    vector<int> camslist;
    int camlistsize=camslist.size();
    for (int i=0 ; i<recsize;i++) {
        string hoodlower=strtolower(Records[i].getneighborhood());
        string interlower=strtolower(Records[i].getintersection());
        camnotinlist=true;
        if(hoodlower.find(newstr)!=string::npos || interlower.find(newstr)!=string::npos) {
            anycams=true;
            for (int j=0; j<camlistsize; j++) {
                if (Records[i].getCameraNumber()==camslist[j]) {
                    camnotinlist=false;
                    break;
                }
            }
            if (camnotinlist==true) {
                camslist.push_back(Records[i].getCameraNumber());
                camlistsize+=1;
            
            cout << "Camera: " << Records[i].getCameraNumber() << endl;
            cout << "Address: " << Records[i].getaddress() << endl;
            cout << "Intersection: " << Records[i].getintersection() << endl;
            cout << "Neighborhood: " << Records[i].getneighborhood() << endl; 
            cout << endl;
            }
        }
    }
    if (anycams==false) {
        cout << "No cameras found." << endl;
    }
}
int main() {
    vector<CameraRecord> Records;
    vector<string> neighborhoodlist;
    string fileName;
    cout << "Enter file to use: ";
    cin >> fileName;
    ReadFile(fileName,Records,neighborhoodlist);

    int choice=0;
    while (choice !=5) {
        cout << "Select a menu option:" << endl;
        cout << "  1. Data overview" << endl;
        cout << "  2. Results by neighborhood" << endl;
        cout << "  3. Chart by month" << endl;
        cout << "  4. Search for cameras" << endl;
        cout << "  5. Exit" << endl;
        cout << "Your choice: ";

        cin >> choice;
        if (choice==1) { // everything is done in functions. Wow the main code looks so clean!
            DataOverview(Records);
        }
        else if (choice==2) {
            ResultsbyHood(Records,neighborhoodlist);
        }
        else if (choice==3) {
            chartbymonth(Records);
        }
        else if (choice==4) {
            cout << "What should we search for? ";
            string inputhood;
            string tempstr; //zybooks 2.14 saved my life here
            getline(cin, tempstr);
            getline(cin, inputhood);
            searchforcams(Records,inputhood);
        }
        else if (choice==5) {
            break;
        }
    }
}