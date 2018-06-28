#include <iostream>
#include <fstream>

using namespace std;

int Load() {
        int num;
        ifstream in("input.txt"); //open file
	while(!in.eof())          //move pointer to last data
	in >> num ;
        in.close();//close
        return num;
}

void Store(int data){
        ofstream out("input.txt", ios::app); //open file & move pointer to end
        out << data << endl;
        //append        
        out.close();
}


int Add(int i,int j){
        return i+j;
}

int main(void) {
        for(int a = 0; a<1000; a++){
                int x = Load();
                x = Add(x,1);
                Store(x);
        }


}

