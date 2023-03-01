#include <iostream>
#include<bits/stdc++.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
#include<climits>
#include <bitset>
#include <ctime>
#include <cassert>
#include <functional>
#include <iomanip>
#include <vector>
#include <stack>
#include <fstream>
//std::ifstream cin("input.txt");
//std::ofstream cout("output.txt");
//freopen("input.txt","r",stdin);
//freopen("output.txt","w",stdout);
//cout<<fixed<<setprecision(*)<<***<<endl;
/*scanf("%d",&..);
printf("%d",..);*/

using namespace std;
bool dcheck = false,checker=false;
map<string, int>mp, mp2; //check about quantity of each product in the super market.
map<int, int>mp3,mp4;
double tot = 0.0, realy = 0, newquantity; //total price,change in price,change in quantity in modify.
int change, l = 0, e = 0, mid = 0, numofid, sure;  //global variables used many times..
vector<pair<int, int> >vec1;  //first is id for each product to search with binary search easy than linear search.,,,second is the index for each product.
struct product
{
	int id; double quantity;
	double price; double discount;    //info for each product.
	string name;
};
// s_p work..
void input(vector<product>&vec, int num, double& tot)  //function to input products.
{
	for (int i = 0; i<num; i++)
	{
		cout << "Enter the id for product " << i + 1 << endl;
		cin >> vec[i].id; mp4[vec[i].id]=1;
		cout << "Enter the name for product " << i + 1 << endl;
		cin >> vec[i].name;
		if (mp2[vec[i].name] == 0) { mp[vec[i].name] = 100; mp2[vec[i].name] = 1; } //check about quantity in super market.
		cout << "Enter the price for product " << i + 1 << endl;             //the information for each product..
		cin >> vec[i].price;
		cout << "Enter the discount for product " << i + 1 << endl;
		cin >> vec[i].discount;
		cout << "Enter the quantity for product " << i + 1 << endl;
		cin >> vec[i].quantity;
		if(vec[i].quantity>mp[vec[i].name])
        {
            cout<<"There is no more than "<<mp[vec[i].name]<<endl;
            cout<<"Enter 1 if you want this quantity or enter any key to refuse "<<endl;
            cin>>sure;
            if(sure==1){vec[i].quantity=mp[vec[i].name];mp[vec[i].name]=100;checker=true;}
            else{vec[i].id=1e8;mp4[vec[i].id]=0;continue;}
        }
		else{mp[vec[i].name] = mp[vec[i].name] - vec[i].quantity;}  //substract the quantity of customer from quantity in super market.
		if (mp[vec[i].name]<50) { cout << "// Warning" << "::" << " " << "product " << vec[i].name << " " << "needed" << endl; mp[vec[i].name] = 100; }
		cout << "Enter " << "1 " << "if you sure about the info for this product " << "or Enter " << "any key" << " if you want to repeat the info" << endl;
		cin >> sure; //warning to modify in info for this product
		if (sure == 1){
			tot = tot + ((double)vec[i].price*vec[i].quantity) - ((double)vec[i].price*(vec[i].discount / 100)*vec[i].quantity);
			vec1.push_back(make_pair(vec[i].id, i)); checker=false;
		}  //to search about id and treat with it from the index.
		else { cout << "so repeat the info" << endl;if(!checker){mp[vec[i].name] = mp[vec[i].name] + vec[i].quantity;}else{mp[vec[i].name]=vec[i].quantity; checker=false;}mp4[vec[i].id]=0; i--; continue; }
	}
}
void inputadd(vector<product>&vec, int fnum, double& tot, int num)  //function to input add products.
{
	for (int i = num; i<fnum; i++)
	{
		cout << "Enter the id for product " << i + 1 << endl;
		cin >> vec[i].id; mp4[vec[i].id]=1;
		cout << "Enter the name for product " << i + 1 << endl;
		cin >> vec[i].name;
		if (mp2[vec[i].name] == 0) { mp[vec[i].name] = 100; mp2[vec[i].name] = 1; }  //check about quantity in super market.
		cout << "Enter the price for product " << i + 1 << endl;             //the information for each product..
		cin >> vec[i].price;
		cout << "Enter the discount for product " << i + 1 << endl;
		cin >> vec[i].discount;
		cout << "Enter the quantity for product " << i + 1 << endl;
		cin >> vec[i].quantity;
		if(vec[i].quantity>mp[vec[i].name])
        {
            cout<<"There is no more than "<<mp[vec[i].name]<<endl;
            cout<<"Enter 1 if you want this quantity or enter any key to refuse "<<endl;
            cin>>sure;
            if(sure==1){vec[i].quantity=mp[vec[i].name];mp[vec[i].name]=100;checker=true;}
            else{vec[i].id=1e8;mp4[vec[i].id]=0;continue;}
        }
		else{mp[vec[i].name] = mp[vec[i].name] - vec[i].quantity;}   //substract the quantity of customer from quantity in super market
		if (mp[vec[i].name]<50) { cout << "// Warning" << "::" << " " << "product " << vec[i].name << " " << "needed" << endl; mp[vec[i].name] = 100; }
		cout << "Enter " << "1 " << "if you sure about the info for this product " << "or Enter " << "any key" << " if you want to repeat the info" << endl;
		cin >> sure; //warning to modify in info for this product
		if (sure == 1) {
			tot = tot + ((double)vec[i].price*vec[i].quantity) - ((double)vec[i].price*(vec[i].discount / 100)*vec[i].quantity);
			vec1.push_back(make_pair(vec[i].id, i)); checker=false;
		} //to search about id and treat with it from the index.
		else { cout << "so repeat the info" << endl;if(!checker){mp[vec[i].name] = mp[vec[i].name] + vec[i].quantity;}else{mp[vec[i].name]=vec[i].quantity;checker=false;} mp4[vec[i].id]=0; i--; continue; }
	}
}
void modify(vector<product>&vec, int fnum, int ch, double& tot)  //function to modify in quantity for customer..
{
	while (ch--)
	{
		l = 0, e = fnum - 1, mid = 0;
		cout << "Enter the id to modify" << endl;
		cin >> numofid; //id to modify the quantity
		cout << "Enter the new quantity do you want to this product" << endl;
		cin >> newquantity;
		if(!mp4[numofid])
        {
            while(!mp4[numofid])
            {
                cout<<"Invalid id"<<endl;
                cout<<"repeat:: Enter the id to modify"<<endl;
                cin>>numofid;
            }

        }
		while (l <= e)  //binary search about numofid in vec1
		{
			mid = (l + e) / 2;
			if (vec1[mid].first == numofid)
			{
			    if(vec[vec1[mid].second].quantity+mp[vec[vec1[mid].second].name]<newquantity)
                {
                    cout<<"There is no more than "<<vec[vec1[mid].second].quantity+mp[vec[vec1[mid].second].name]<<endl;
                    cout<<"Enter 1 if you want this quantity or enter any key to refuse "<<endl;
                    cin>>sure;
                    if(sure==1){cout<<"Enter the new quantity you want"<<endl; cin>>newquantity;}
                    else
                    {
                        cout<<"Enter the new quantity you want"<<endl; //check quantity about customer.
                        cin>>newquantity;
                    }
                }
				mp[vec[vec1[mid].second].name] = mp[vec[vec1[mid].second].name] + (vec[vec1[mid].second].quantity - newquantity); //the difference between old and new quantity
				if (mp[vec[vec1[mid].second].name]<50) { cout << "// Warning" << "::" << " " << "product " << vec[vec1[mid].second].name << " " << "needed" << endl; mp[vec[vec1[mid].second].name] = 100; }
				realy = ((double)vec[vec1[mid].second].price*vec[vec1[mid].second].quantity) - ((double)vec[vec1[mid].second].price*(vec[vec1[mid].second].discount / 100)*vec[vec1[mid].second].quantity);
				tot = tot - realy; //substract old price.
				vec[vec1[mid].second].quantity = newquantity;
				realy = ((double)vec[vec1[mid].second].price*vec[vec1[mid].second].quantity) - ((double)vec[vec1[mid].second].price*(vec[vec1[mid].second].discount / 100)*vec[vec1[mid].second].quantity);
				tot = tot + realy; //add new price.
				break;
			}
			else if (vec1[mid].first<numofid) { l = mid + 1; }
			else { e = mid - 1; }
		}
	}
}
void deletee(vector<product>&vec, int fnum, int ch, double& tot) //function to delete
{
	while (ch--)
	{
		l = 0, e = fnum - 1, mid = 0;
		cout << "Enter the id for product to delete" << endl;
		cin >> numofid;
		if(!mp4[numofid])
        {
            while(!mp4[numofid])
            {
                cout<<"Invalid id"<<endl;
                cout<<"repeat:: Enter the id to delete"<<endl;
                cin>>numofid;
            }
        }
		while (l <= e)
		{
			mid = (l + e) / 2;
			if (vec1[mid].first == numofid)
			{
				if (mp3[vec1[mid].first] == 1) { dcheck = true; break; }  //check if product deleted or not
				mp3[vec1[mid].first] = 1;
				mp[vec[vec1[mid].second].name] += vec[vec1[mid].second].quantity; //put all quantity for this product in super market
				realy = ((double)vec[vec1[mid].second].price*vec[vec1[mid].second].quantity) - ((double)(vec[vec1[mid].second].price*(vec[vec1[mid].second].discount / 100))*vec[vec1[mid].second].quantity);
				tot = tot - realy; //substract the price or this product.
				vec[vec1[mid].second].id = 1e8;  //don,t appear in invoice.
				break;
			}
			else if (vec1[mid].first<numofid) { l = mid + 1; }
			else { e = mid - 1; }
		}

	}
}
void output(vector<product>&vec, int fnum) //output invoice.
{
	cout << endl << endl << "************************************************" << endl;
	cout << "the invoice" << endl;
	cout << "***********" << endl;
	cout << "the product id" << "  " << "the product name" << "  " << "the product price" << "  " << "the product discount" << "  " << "the product quantity" << endl;
	for (int i = 0; i<fnum; i++)
	{
		if (vec[i].id != 1e8) //check if it delete or not..
			cout << vec[i].id << "        " << vec[i].name << "        " << vec[i].price << "        " << vec[i].discount << "         " << vec[i].quantity << endl;
	}
	cout << "******************************************************" << endl;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1e8;
	while (t--) {
		int numofproduct;
		cout << "Enter the number of product" << endl;
		cin >> numofproduct; //the number of product the customer need to buy.
		if (numofproduct<0)
		{
			while (numofproduct<0)
			{
				cout << "invalid number" << endl;   // check if it invalid or valid number.
				cout<<"repeat:: Enter the number of product"<<endl;
				cin >> numofproduct;
			}
		}
		vector<product>vec(numofproduct);
		input(vec, numofproduct, tot);   //sequence of product.
		cout << "Enter the number of add product" << endl;
		cin >> change; //number of add product
		if (change<0)
		{
			while (change<0)
			{
				cout << "invalid number" << endl;   // check if it invalid or valid number.
				cout<<"repeat:: Enter the number of add product"<<endl;
				cin >> change;
			}
		}
		int finalsize = (numofproduct + change);  //first+add(product)..
		vec.resize(finalsize);
		inputadd(vec, finalsize, tot, numofproduct);   //sequence of add product.
		sort(vec1.begin(), vec1.end());
		cout << "Enter the number of modify products" << endl;
		cin >> change;  //the number of modify products
		if (change<0)
		{
			while (change<0)
			{
				cout << "invalid number" << endl;   // check if it invalid or valid number.
				cout<<"repeat:: Enter the number of modify product"<<endl;
				cin >> change;
			}
		}
		modify(vec, finalsize, change, tot);  //call to modify
		cout << "Enter the number of delete product" << endl;
		cin >> change;
		if (change<0)
		{
			while (change<0)
			{
				cout << "invalid number" << endl;   // check if it invalid or valid number.
				cout<<"repeat:: Enter the number of delete product"<<endl;
				cin >> change;
			}
		}
		deletee(vec, finalsize, change, tot);  //call to delete
		output(vec, finalsize);  //call to output the invoice.
		cout << endl;
		cout << "the total price is" << endl;
		if (tot>0 && change != finalsize)
			cout << tot << endl; //final prince
		else
		{
			if (change == finalsize)
			{
				if (!dcheck)
				{
					cout << 0 << endl;
				}
				else { cout << tot << endl; }
			}
			else { cout << 0 << endl; }
		}
		cout << endl << endl << endl;
		char check;
		cout << "Enter 'D' to finish or enter 'any character' to continue make an invoice for another customer" << endl;
		cin >> check;
		if (check == 'D') { break; }
		vec.clear();  //clear all vec..
		vec1.clear(); //clear all vec1 first and second..
		mp3.clear();  //clear to delete for another customer.
		tot = 0; //start with tot=0 for new customer..
		dcheck = false;
		checker=false;
		continue;
	}
	return 0;
}
