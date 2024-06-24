#pragma once
#include <iostream>
#include "Player.h"

class Leg {
	Player player1;
	Player player2;
	int points1;
	int points1Mid;
	int points2;
	int points2Mid;
	int legScore1;
	int legScore2;
public:
	Leg(string& p1, string& p2) : points1(501), points1Mid(501), points2(501), points2Mid(501), legScore1(0), legScore2(0) {
		player1.setName(p1);
		player2.setName(p2);
	}
	Leg() : points1(501), points1Mid(501), points2(501), points2Mid(501), legScore1(0), legScore2(0) {}

	void setNames(string& p1, string& p2) {
		player1.setName(p1);
		player2.setName(p2);
	}

	int calcScore(const string& p, int points, bool fl) {
		if (p == player1.getName()) {
			int changePoints = points1Mid - points;
			if (changePoints > 1 || (changePoints == 0 && fl))
			{
				points1Mid = changePoints;
				return points1Mid;
			}
			else
			{
				points1Mid = points1;
				return changePoints;
			}
		}
		else if (p == player2.getName()) {
			int changePoints = points2Mid - points;
			if (changePoints > 1 || (changePoints == 0 && fl))
			{
				points2Mid = changePoints;
				return points2Mid;
			}
			else
			{
				points2Mid = points2;
				return changePoints;
			}
		}
	}

	string legWinsInString(const string& p) const{
		if (p == player1.getName()) {
			string str = "Leg wins: " + to_string(legScore1);
			return str;
		}
		else if (p == player2.getName()) {
			string str = "Leg Wins: " + to_string(legScore2);
			return str;
		}
	}

	int legWinsInInt(const string& p) const {
		if (p == player1.getName()) {
			return legScore1;
		}
		else if (p == player2.getName()) {
			return legScore2;
		}
	}

	void setLegWins(const string& p) {
		if (p == player1.getName()) {
			legScore1++;
		}
		else if (p == player2.getName()) {
			legScore2++;
		}
		points1 = 501;
		points1Mid = 501;
		points2 = 501;
		points2Mid = 501;
	}

	void resetScores()  {
		points1 = 501;
		points1Mid = 501;
		points2 = 501;
		points2Mid = 501;
		legScore1 = 0;
		legScore2 = 0;
	}

	void changeCurrentScore() {
		points1 = points1Mid;
		points2 = points2Mid;
	}

	void restoreMidPoints() {
		points1Mid = points1;
		points2Mid = points2;
	}

	string getCurrentScore(string& p) const {
		if (p == player1.getName()) {
			string str = "Score: " + to_string(points1);
			return str;
		}
		else if (p == player2.getName()) {
			string str = "Score: " + to_string(points2);
			return str;
		}
	}
};