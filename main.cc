/* Deze opdracht is gemaakt door
 * Tim Poot (s1514113) en Ruben van der Waal (s1559451)
 * Voor de opdracht 3: Expressies van het vak datastructuren
 *
 * Met dit programma kan de gebruiker via de commandline een expressie
 * invoeren die vervolgens wordt opgeslagen in het programma als een
 * boom. Hierna kan de gebruiker, weer via de commandline, een aantal
 * acties uitvoeren op de boom zoals:  differentieren, versimpelen en
 * evalueren voor een bepaalde waarde voor x.
*/


#include <iostream>
#include "ExpressionTree.h"
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

void infoblokje(){
  cout << "------------------------------------------------" << endl;
  cout << "|Dit programma is gemaakt door:                |" << endl;
  cout << "|Tim Poot & Ruben van der Waal                 |" << endl;
  cout << "|Input geven door karakters in te vullen en    |" << endl
       << "|vervolgens enter te drukken                   |" << endl;
  cout << "------------------------------------------------" << endl;
}//infoblokje

int main(){
  string input;
  string s;
  ExpressionTree myTree;
  bool exit = false;

  infoblokje();

  while(!exit){
    cout << "Voer een commando in:" << endl;
    cin >> input;

    if(input == "end"){
      exit = true;
    }else if(input == "exp"){
      getline(cin, input);
      input.erase(0, 1);
      myTree.parse(input);
    }else if(input == "eval"){
      getline(cin, input);
      input.erase(0, 1);
      myTree.evaluate('x', atof(input.c_str()));
    }else if(input == "simp"){
      myTree.simplify();
    }else if(input == "print"){
      myTree.showInOrder();
    }else if(input == "dot"){
      cout << "dit moet nog, label is gonezo, cannot be bothered atm" << endl;
      //getline(cin, input);
      //input.erase(0, 1);
      //myTree.saveAsDot(input, "expression");
    }else if(input == "diff"){
      myTree.differentiate();
    }
  }

  cout << "Programma sluit af." << endl;

  return 0;
}

