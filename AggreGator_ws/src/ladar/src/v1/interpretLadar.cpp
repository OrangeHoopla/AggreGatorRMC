//
//  interpretRanges.cpp
//
//  Created by Joey Siracusa on 3/25/14.
//

#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <cmath>
#include <sstream>
#include "ladar/ladar_data.h"

using namespace std;

/*
    to_string not a function in roscpp, so using this because works
*/
string ghetto_to_string(float number){
    ostringstream buffer;
    buffer << number;
    return buffer.str();
}//end to_string

Ladar::Ladar(int numOfSamples): thetas(numOfSamples),
    degrees(numOfSamples),
    coords(numOfSamples){
    
}

/*
    getCoordinates
          - Uses laser.ranges[] array, along with other laser member variables, 
            to convert the polar coordinates into cartesian coordinates 
          - Returns as vector of pairs.  First element of pair is x, second element is y.

*/
vector<pair<float, float> > Ladar::getCoordinates(	float* ranges, int numOfSamples, 
											float angle_min, float angle_increment,
                                            float min_range, float max_range){

    vector<pair<float, float> > coordinates(numOfSamples);
    float theta;
    float x;
    float y;
    
    //converts index into theta based on angle_min and angle_increment
    //then converts polar (range, theta) into cartesian (x,y)
    
    
    for(int i = 0; i < numOfSamples; i++){
        theta = i*angle_increment + angle_min;
        this->degrees.push_back(theta*57.296);
         //calculate theta assuming LADAR as origin
        if(ranges[i] > min_range && ranges[i] < max_range){
            //if the range meets the range constraints, push coordinates to vector
            x = ranges[i]*cos(theta); //calculate x coordinate
            y = ranges[i]*sin(theta); //calculate y coordinate
            pair<float, float> curr(x,y);
            coordinates.push_back(curr); //push to coordinates vector
            this->coords.push_back(curr);
            this->thetas.push_back(theta);
        }
        //else, do not push coordinates to vector; they are not accurate
        
    }

    return coordinates;
}//end getcoordinates

/*
	fivePointAverager
		-Adds together every five x and y values into currXSum and currYSum
		-On the fifth value, divide both currXSum and currYSum by 5
		-Push this averaged pair onto the filtered vector, reset the sums
*/

vector<pair<float, float> > Ladar::fivePointAverager(vector<pair<float, float> > original){
    vector<pair<float, float> > filtered;
    float currXSum = 0;
    float currYSum = 0;
    
    for(int i = 0; i < original.size(); i++){
        currXSum = currXSum + original[i].first; //add together every five x values
        currYSum = currXSum + original[i].second; //add together every five y values
        if((i+1)%5 == 0){
            //if the next index is a multiple of five
            //save the averaged pair in the filtered vector, and reset the current sums
            pair<float, float> curr(currXSum/5, currYSum/5);
            filtered.push_back(curr);
            currXSum = 0;
            currYSum = 0;
            
        }
        
    }
    
    return filtered;
}//end averager

/*
	coordinatesToString
		-Creates a string out of a vector of pairs.
		Format:	
		"(x, y) (x, y) (x, y) (x, y) (x, y) (x, y) (x, y) (x, y) (x, y) (x, y) 
		 (x, y) (x, y) (x, y) (x, y) (x, y) (x, y) (x, y) (x, y) (x, y) (x, y) "...
*/

string Ladar::coordinatesToString(vector<pair<float, float> > coordinates){
    string coordString;
    for(int i = 0; i < coordinates.size(); i++){
        coordString +=  string("(") + ghetto_to_string(coordinates.at(i).first) + string(", ")
                                    + ghetto_to_string(coordinates.at(i).second) + string(") ");
        
        if((i+1)%10 == 0){
        	//only print 10 coordinates per line
        	coordString += string("\n");
        }
    }
    
    return coordString;
}//end coordinatestostring


/*Prints out 
*/
void Ladar::print(vector<float> choice, string type){
    for(int i = 0; i < choice.size() && i < coords.size(); i++){
        string coord = string("(") + ghetto_to_string(coords.at(i).first) + string(", ")
                                    + ghetto_to_string(coords.at(i).second) + string(") m,m");
        cout << choice.at(i) << " " << type << " :  " << coord << endl;
    }
}

void Ladar::print(int choice){
    switch(choice){
        case 0:{
            print(this->thetas, "radians");
            break;
        }
        case 1:{
            print(this->degrees, "degrees");
            break;
        }
        default: break;
    }
}


//NOTE: Any value < 0.1 is like literally touching the ladar

bool Ladar::forwardCheck(){
    //make check for forward facing ladar
}

bool Ladar::leftCheck(){}
bool Ladar::rightCheck(){}

//potentially create functions for determining actual degrees, not in radians
//ladar scans counterclockwise, so mark with sticky note or something which way, during tests

