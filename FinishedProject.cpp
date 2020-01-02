#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

struct table{
	bool filled;
  	//starting point coord
  	int x;
  	int y;
  	int length;
  	int width;
  	table(int x1, int y1, int len, int wid, bool fill)
  	{
  		  x = x1; 
  		  y = y1;
  		  length = len;
  		  width = wid;
  		  filled = fill;
  	}
};

//meals being ordered 
struct meal{
	string nameMeal;
	double price;
  	meal(string nameMeal1, double price1)
  	{
    		nameMeal = nameMeal1;
		price = price1;
  	}
};
 
//customer ordering meal

struct customer{
	string name;
	vector <meal> order;
  	customer(string name1, vector<meal> order1){
    		name = name1;
    		order = order1;
  	}
};

struct node{
	customer* cust = NULL;
    	node* next = NULL;
};

struct group{
	table* t = NULL;
	string groupName;
 	 int size;
 	 vector<customer> names;
 	 group(int s1, vector<customer> n1, string gn1){
 		size = s1;
 		names = n1;
 		groupName = gn1;
 	 }
};

//global class encompassing customers and meals
class restaurant{
	double revenue = 0;
	vector <group> sitting;
	vector <meal> menu;
  	vector <table> seating;
	node* front = NULL;
	node* rear = NULL;
	char floor[11][13] = {
        	{' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' '},
        	{' ','#','#','#',' ','#','|',' ',' ','B','A','R',' '},
		{' ','#','#','#',' ',' ','|',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ','#','|',' ',' ',' ',' ',' ',' '},
		{' ','#','#','#',' ',' ','-','-','-','-','-','-','-'},
		{' ','#','#','#',' ',' ',' ','#',' ','#',' ','#',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ','#','#',' ','#','#',' ','#','#','#','#','#',' '},
		{' ','#','#',' ','#','#',' ','#','#','#','#','#',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

	public:
	
	void addmeal(string name, double price){
		menu.push_back(meal(name, price));
	}
	
	restaurant(string filename){
		string name, price, temp;
		ifstream ifstrm; 
		ifstrm.open(filename);
		while(getline(ifstrm, temp)){
			stringstream sstrm(temp);
			getline(sstrm, name, ',');
			getline(sstrm, price, ',');
			addmeal(name, stod(price));
		}
		addtables();
	}

	void addtables(){
        seating.push_back(table(1,1,3,2,0));
        seating.push_back(table(1,4,3,2,0));
        seating.push_back(table(1,8,2,2,0));
        seating.push_back(table(4,8,2,2,0));
        seating.push_back(table(7,8,5,2,0));
        seating.push_back(table(5,1,1,1,0));
        seating.push_back(table(5,3,1,1,0));
        seating.push_back(table(7,5,1,1,0));
        seating.push_back(table(9,5,1,1,0));
        seating.push_back(table(11,5,1,1,0));
	}

	void enqueue(customer* c){
		node *temp = new node();
	    	temp->cust = c;
	    	temp->next = NULL;
	    	if(front == NULL){
	        	front = temp;
	        	rear = temp;
		}
	    	else{
	        	rear->next = temp;
	        	rear = temp;
	    	}
	}
	
	void dequeue(){
	    	if(front == NULL){
	    		cout<<"queue is empty"<<endl;
	    	    	return;
	    	}
	    	else{
	    	    	node *temp = front;
	    	    	front = front->next;
	    	    	delete temp;
	    	}
	}
	
	customer* linefront(){
		return front->cust;
	}	
	
	void printline(string cname){
		int counter = 1;
		cout << "ordering list: " << endl;
		node *temp = front;
		if(front == NULL){
			cout << "The line is empty" <<endl;
			return;
		}	
		while(1){
			cout << "name: " << temp->cust->name;
			if(temp->cust->name == cname){
				cout << "  <----- #" << counter << endl;
				return;
			}
			cout<<endl;
			if(temp->next == NULL)
				return;
			temp = temp->next;
			counter++;
		}
	}

	void filltable(table* t){
		for(int c = t->x; c < t->x+t->length; c++){
			for(int r = t->y; r< t->y+t->width; r++){
                	floor[r][c] = 'X';
            		}
		}
		t->filled = true;
	}

	void unfilltable(table* t){
		for(int c = t->x; c < t->x+t->length; c++){
			for(int r = t->y; r<t->y+t->width; r++){
                	floor[r][c] = '#';
            		}
		}
		t->filled = false;
	}
    
	void printmenu(){
		for(meal m: menu){
			string c = to_string(m.price);
			c = c.substr(0, c.length()-4);
			cout << "name: " << m.nameMeal << "   " << "price: $" << c << endl;
		}
	}
	
	void addorder(string name, vector <meal> orders){
    		customer* c = new customer(name, orders);
    		enqueue(c);
	}
	
	void removeorder(){
		if(front == NULL){
			cout << "The line is empty" <<endl;
			return;
		}	
		cout << "Finished "<< linefront()->name <<"'s Order" << endl;
		dequeue();
	}

	void removemeal(string m1){
		for(int i = 0; i< menu.size(); i++){
      			if(menu[i].nameMeal == m1){
        		    	cout << "Removed " << m1 << " from the menu." << endl;
				menu.erase(menu.begin()+i);
				return;
      			}
    		}
		cout << m1 << " Does not exist on the menu." << endl;
	} 
	
  	void seatgroup(group g){
  	        g.t = openseats(g.size);
  	        if(g.t == NULL){
  	      		cout << "No table available."<<endl;
  	        }
  	        else{
  	      		cout << "Available table, seated." << endl;
  	      		sitting.push_back(g);
  	      		filltable(g.t);
  	        }
  	}

  	void leaverestaurant(string name){
  	        for(int i = 0; i < sitting.size(); i++){
  	      	  	if(sitting[i].groupName == name){
  	      	  		printreceipt(sitting[i]);
  	      	  	      	unfilltable(sitting[i].t);
  	      	  	      	sitting.erase(sitting.begin()+i);
  	      	  	}
  	        }
  	}
  	
  	void printreceipt(group g)
  	{
  		double grouptotal = 0;
  		cout<<"Group Name: "<<g.groupName<<endl;
  		for(int i = 0; i<g.names.size(); i++)
  		{
  		       double total = 0;
  		       cout<<"Customer "<<i+1<<": "<<g.names[i].name<<endl;
  		       for(int j = 0; j<g.names[i].order.size(); j++)
  		       {
  				cout<<g.names[i].order[j].nameMeal<<"\t\t$"<<g.names[i].order[j].price<<endl;
  				revenue += g.names[i].order[j].price;
  				total += g.names[i].order[j].price;
  				grouptotal += g.names[i].order[j].price;
  		       }
  		       cout<<"Customer Total: $"<<total<<endl;
  		}
  	 	cout << "Group Total: $" <<grouptotal<<endl;
  	}

  	//return empty seats for party
  	table* openseats(int size){ 
  	      	int difference = 40;
  	      	table *t = NULL;
  	      	for(int i = 0; i < seating.size(); i++){
  	      		if((seating[i].filled == false)&&(size <= seating[i].length*seating[i].width)){
  	      			if(seating[i].length*seating[i].width - size < difference){
  	      				difference = seating[i].length*seating[i].width - size;
  	      				t = &seating[i];
  	      			}
  	      		}
  	      	}
  	      	return t;
  	}

	double totalRevenue(){
		return revenue;
	}

    	void printMatrix(){
    		for(int i = 0; i<11; i++){
    		    	for(int j = 0; j<13; j++){
    		    	    	cout<< " " << floor[i][j];
    		    	}
    		    	cout<<endl;
    		}
    	}

	vector<meal> returnMenu()
	{
	    	return menu;
	}
	
	void closerestaurant(){
		while(front != NULL)
			dequeue();
		sitting.clear();
		menu.clear();
	  	seating.clear();
	}

	void printgroup(){
		if(sitting.size() == 0){
			cout << "No one is seated" << endl;
			return;
		}
		int counter = 1;
		for(group g : sitting){
			cout << "group " <<counter << ": " <<g.groupName <<endl;
			counter++;
		}
	}
};

int main(int argc, char *argv[]){
	
	//handles interface
	restaurant r(argv[1]);
	int cmd;
	while(cmd != 3){
		cout<<"========================="<<endl;
		cout<<"Welcome to Chimp Express!"<<endl;
		cout<<"========================="<<endl;
		cout<<endl;
		cout<<"Pick an Option"<<endl;
        	cout<<"1. Cook Interface"<<endl;
        	cout<<"2. Customer Interface"<<endl;
		cout<<"3. Quit"<<endl;
        	cin >> cmd;
		switch(cmd){
			case 1:
				cout << "Welcome Cook" << endl;
				while(cmd!=6){
					cout << "Pick an Option" << endl;
					cout << "1. Remove Customer from Line (order finished)" << endl;
					cout << "2. View Total Revenue" << endl;
					cout << "3. Add Meal to a Menu" << endl;
					cout << "4. Remove Meal from Menu" << endl;
        	        		cout << "5. Print Menu"<<endl;
					cout << "6. Go Back to Interface Selection" << endl;
					cin >> cmd;
					if(cmd == 1){
						r.removeorder();
					}
					if(cmd == 2){
						string c = to_string(r.totalRevenue());
						c = c.substr(0, c.length()-4);
						cout << "Total Revenue: " << c << endl;
					}
					if(cmd == 3){
						string name, price;
						cout << "Input Meal Name: " <<endl;
						cin.clear();
						cin.ignore();
						getline(cin, name);
						cout << "Input Price" << endl;
						cin.clear();
						getline(cin, price);
						r.addmeal(name, stod(price));
					}
					if(cmd == 4){
						string name;
						cout << "Input Meal Name: " <<endl;
						cin.clear();
						cin.ignore();
						getline(cin, name);
						r.removemeal(name);
					}
					if(cmd == 5){
						r.printmenu();
					}
					cout<<endl;
				}
				break;
			case 2:
				{
				cout << "Welcome Valued Customer" << endl;
				while(cmd != 7){
					cout << "Pick an Option" << endl;
					cout << "1. Seat Group and Place Order" << endl;
					cout << "2. Print Menu" << endl;
					cout << "3. Print Tables" << endl;
					cout << "4. Print Groups" << endl;
					cout << "5. Print Place in Line" << endl;
					cout << "6. Ask for Check" << endl;
					cout << "7. Go Back to Interface Selection" << endl;
                			cin>>cmd;
					if(cmd == 1){
						int sizeg;
						string cname, gname;
                    				string mealname;
						vector <meal> temporder;
						vector <customer> tempcustomer;
                    				vector <meal> tempmenu = r.returnMenu();
						cout << "What is the size of the group?" << endl;
						cin >> sizeg;
						table * temp = r.openseats(sizeg);
						if(temp == NULL){
							cout << "All the tables are filled" << endl;
							continue;
						}
						cout << "What is the group name?" << endl;
						cin >> gname;
						for(int i = 0; i < sizeg; i++){
                        				cout<<"What is the name of customer " << i+1 << "?" <<endl;
							cin  >> cname;
							cout <<"Place Order: "<<endl;
                        				cout <<"Enter meal item: (enter Q to end)"<<endl;
							cin.clear();
							cin.ignore();
							getline(cin, mealname);
							while(mealname != "Q"){
                            					for(int j = 0; j<tempmenu.size(); j++)
                            					{
                            					    if(tempmenu[j].nameMeal == mealname)
                            					    {
                            					        temporder.push_back(tempmenu[j]);
                            					    }
                            					}
                            					cout<<"Enter meal item: (enter Q to end)"<<endl;
                            					cin.clear();
								getline(cin, mealname);
                        				}
							customer c(cname, temporder);
							r.addorder(cname, temporder);
							tempcustomer.push_back(c);
							temporder.clear();
						}
						group g(sizeg, tempcustomer, gname);
						r.seatgroup(g);
						tempcustomer.clear();
					}
                			if(cmd == 2)
                			{
                			    	r.printmenu();
                			}
					if(cmd == 3){
                    				r.printMatrix();
					}
					if(cmd == 4){
                    				r.printgroup();
					}
					if(cmd == 5){
						string name;
						cout << "Enter name of person" << endl;
						cin>> name;
						r.printline(name);
					}
					if(cmd == 6){
						string name;
                    				cout << "Enter group name"<< endl;
						cin>>name;
						r.leaverestaurant(name);
					}
					cout<<endl;
				}
				break;
			}
		}
	}
	cout<<"Goodbye!"<<endl;
	r.closerestaurant();
	return 0;
}
