/**------------------------------------------

    Program 4: IMDB

    Course: CS 141, Fall 2022.
    System: Windows 11
    Student Author: Harket Ghuman
-------------------------------------------*/
#include <sstream>
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

/*********************************************** Helper functions ***************************************/
//The splitString function takes a line and split it on the delimiter and push the parts into user_search
void splitString(string line, char delimiter, vector<string>& user_search ) {
    stringstream s_stream(line);
    while (s_stream.good()) {
        string item;
        getline(s_stream, item, delimiter);
        user_search.push_back(item);
    }
}
/**********************************************************************************************************/

//all structures needed for data memebers in the files.
/**********************************************************************************************************/
struct TitleRecord {
    string titleid;
    string startYear;
    string primarytitle;
    string genres;
};
struct PrincipalRecord {
    string titleidprincipal;
    string nameidprincipal;
    string character;
};
struct NameRecord {
    string nameid;
    string primaryName;
    string birthYear;
    string deathYear;
    string primaryProfession;
};


/**********************************************************************************************************/



void menu (vector<TitleRecord> &movieTitles, vector<NameRecord> &movieNames,vector<PrincipalRecord> &moviePrincipals); // For the search function.
//
//bool findInVec (vector<unsigned> movies , string word , int option){
//    string strucData;
//    if (option == 1){
//        strucData = "primarytitle";
//    }
//    else{
//        strucData = "primaryName";
//    }
//    for (int i=0; i<movies.size(); i++) {
//        int temp = 0;
//        while (temp < word.size()) {//help from https://www.geeksforgeeks.org/string-find-in-cpp/
//            if (lower_search_string(movies[i].strucData).find(word[temp]) != string::npos) {
//                temp++;
//            } else {
//                break;
//            }
//
//        }
//    }
//
//}


string make_lower(string word){
    string lower = "";
    for(int i = 0;i < word.size();i++){
        lower += tolower(word[i]);
    }
    return lower;
}

string string_lower (string &s1){

    // using transform() function and ::toupper in STL
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
}
//Choice one searching for movies
void option1(vector<TitleRecord> movieTitles, vector<NameRecord> movieNames,vector<PrincipalRecord> moviePrincipals, string input) {
    vector<string> elements;
    string lower_search= make_lower(input);
    splitString(lower_search, '+', elements );
    int count=0;
    vector<TitleRecord> allMovies;

    for (int i=0; i<movieTitles.size(); i++) {
        int temp=0;

        while (temp < elements.size()) {//help from https://www.geeksforgeeks.org/string-find-in-cpp/
            if (make_lower(movieTitles[i].primarytitle).find(elements[temp]) != string::npos)  {
                temp++;
            }
            else{
                break;
            }

        }




        if (temp == elements.size()) { // printing the movie
            cout << count <<":"<< endl ;
            count++;
            cout<< "Title: "<< movieTitles[i].primarytitle << endl;
            cout <<"Year: " << movieTitles[i].startYear << endl;
            vector<string> realgenres;
            splitString(movieTitles[i].genres, ',', realgenres);
            cout << "Genres: ";
            for(int j = 0; j < realgenres.size(); j++) {
                cout << " " << realgenres.at(j);
            }
            cout <<  endl;
            cout<< "---------------"<< endl;

            allMovies.push_back(movieTitles[i]);
        }
    }


    if(allMovies.size() == 0){ // if no movies are found
        cout << "No match found!" << endl;
    }
    cout << "Select a movie to see its actor/actress (-1 to go back to the previous menu): "<<endl;
    int choice;// help from TA
    cin >> choice; // finding the charachters involved.
    vector<NameRecord> actors;
    vector<PrincipalRecord> roles;
    for(int i = 0 ;i < moviePrincipals.size();i++){
        if(moviePrincipals[i].character != "\\N" && allMovies[choice].titleid == moviePrincipals[i].titleidprincipal  ){ // if the charchter exists for that title id.
            for(int j = 0; j< movieNames.size();j++){
                if(moviePrincipals[i].nameidprincipal == movieNames[j].nameid){
                    actors.push_back(movieNames[j]);
                    roles.push_back(moviePrincipals[i]);
                }
            }
        }
    }
    for (int c = 0 ; c < actors.size() ; c++){ // printing the charachters
        cout << actors.at(c).primaryName <<" " << roles.at(c).character << endl;
    }
}
//help from https://www.geeksforgeeks.org/string-find-in-cpp/
void option2( string word, vector<TitleRecord> movieTitles, vector<NameRecord> movieNames,vector<PrincipalRecord> moviePrincipals) {
    string lower_search= make_lower(word);
    vector<string> user_search;
    splitString(lower_search, '+', user_search );
    vector<NameRecord> allMovies2;
    int count=0;
    for (int i=0; i<movieNames.size(); i++) {
        int count2=0;
        while (count2 < user_search.size()) {
            if (make_lower(movieNames[i].primaryName).find(user_search[count2]) != string::npos)  { // using .find linear search
                count2++;
            }

            else{
                break;
            }

        }
        if (count2== user_search.size()) {
            cout << count <<":"<< endl ;
            cout<< "---------------" << endl;
            cout<< movieNames[i].primaryName << endl;
            cout << movieNames[i].primaryProfession << endl;
            cout << "(" << movieNames[i].birthYear << "-" << movieNames[i].deathYear << ")" << endl;
            cout<< "---------------"<< endl;
            allMovies2.push_back(movieNames[i]);
            count++;
        }
    }
    if(allMovies2.size() == 0){
        cout << "No match found"<<endl;
    }
    cout << "Select an actor/actress to see movie (-1 to go back to the previous menu): " << endl;
    int choice;
    cin >> choice;
    if(choice == -1){
        menu(movieTitles, movieNames, moviePrincipals);
        return;
    }

    for(int i = 0 ;i < moviePrincipals.size();i++){
        if(allMovies2[choice].nameid == moviePrincipals[i].nameidprincipal){
            for(int j = 0; j< movieTitles.size();j++){
                if(moviePrincipals[i].titleidprincipal == movieTitles[j].titleid){
                    cout << movieTitles[j].primarytitle << " " << movieTitles[j].startYear << " " << moviePrincipals[i].character << endl;
                }
            }

        }
    }
    cout << "Select an actor/actress to see movie (type done to go back to the previous menu): " << endl; // searching for actresses
    string option;
    cin >> option;
    if(option == "done"){
        menu(movieTitles, movieNames, moviePrincipals);
        return;
    }
    else{
        option2(option, movieTitles, movieNames,moviePrincipals);
    }

}

// printing full menu
void menu (vector<TitleRecord> &movieTitle, vector<NameRecord> &movieName,vector<PrincipalRecord> &moviePrinciple) {
    int choice;

    while(choice != 3) { // do print the menu until user quits.
        cout << "Select a menu option" << endl;
        cout<< "    1. Search for movie"<< endl;
        cout<< "    2. Search for actor/ actresses"<< endl;
        cout<< "    3. Exit"<< endl;
        cout<< "Your choice --> ";
        cin >> choice;
        string choice2;
    switch(choice) {
        case (1):
            cout << "Enter search phrase: ";
            cin >> choice2;
            option1(movieTitle, movieName, moviePrinciple, choice2);
            cout << "----------------" << endl;
            break;

        case (2):
            cout << "Enter search phrase: " << endl;
            cin >> choice2;
            option2(choice2 , movieTitle, movieName, moviePrinciple);
            break;
        }

        break;


    }

}


// reading and sending bacK data on title file
vector<TitleRecord> fileReadTitle (string name ){
    vector<string> allMovies;
    vector<TitleRecord> TitleMovies;
    fstream file;
    file.open(name);
    string movie;

    while(getline(file, movie)){
        splitString(movie, '\t' , allMovies);
    }

    TitleRecord currMovie;

    for (int i = 0 ; i < allMovies.size() ; i += 9){
        currMovie.titleid = allMovies.at(i);
        currMovie.startYear = allMovies.at(i+5);
        currMovie.genres = allMovies.at(i+8);
        currMovie.primarytitle = allMovies.at(i+2);
        TitleMovies.push_back(currMovie);
    }
    file.close();
    return TitleMovies;
}

// reading and sending bacK data on movie name file
vector<NameRecord> fileReadName (string name ) {

    ifstream file;
    string line;
    vector<NameRecord> allMovies;
    file.open(name);
    while(getline(file,line)){
        vector<string> namesTitles;
        splitString(line,'\t',namesTitles);
        NameRecord currMovie;
        currMovie.nameid = namesTitles[0];
        currMovie.primaryName =namesTitles[1];
        currMovie.birthYear = namesTitles[2];
        currMovie.deathYear = namesTitles[3];
        currMovie.primaryProfession = namesTitles[4];

        allMovies.push_back(currMovie);
    }
    return allMovies;
}

//Reading and sending back all movie principal data.
vector<PrincipalRecord> fileReadPrincipal (string name){
    PrincipalRecord currMovie;
    vector<PrincipalRecord> moviePrincipals;

    ifstream file;
    string line;
    file.open(name);
    while(getline(file,line)){
        vector<string> titles;
        splitString(line,'\t',titles);
        currMovie.titleidprincipal = titles[0];
        currMovie.nameidprincipal = titles[2];
        currMovie.character =  titles[5];
        moviePrincipals.push_back(currMovie);
    }
    file.close();
    return moviePrincipals;
}

//read all data needed in this function.
int run(string titlesFile, string namesFile, string principalsFile) {
    vector<TitleRecord> titleVector = fileReadTitle(titlesFile);
    vector<NameRecord> nameVector = fileReadName(namesFile);
    vector<PrincipalRecord> principalVector = fileReadPrincipal(principalsFile);

    menu(titleVector, nameVector, principalVector);
    return 0;
}


int main() {


    string titlesFile =	"C:\\Users\\harke\\OneDrive\\Desktop\\Computer lab\\New folder\\movie.titles.tsv";
    string namesFile = "C:\\Users\\harke\\OneDrive\\Desktop\\Computer lab\\New folder\\movie.names.tsv";
    string principalsFile = "C:\\Users\\harke\\OneDrive\\Desktop\\Computer lab\\New folder\\movie.principals.tsv";

    //DO NOT change the main function. The main function will be removed by the autograder
    run(titlesFile, namesFile, principalsFile);

    return 0;
}
