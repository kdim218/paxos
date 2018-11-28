#include <bits/stdc++.h>

using namespace std;

//
// Input
//   -items   : vector of <string, int> pairs representing item name and price
//   -giftCard: value of the giftCard that we want to spend
//
// Output
//   None. Print out the two most expensive items we can afford with our card,
//         otherwise "Not possible." if there is nothing we can afford
//
// First, we sort the items by price. Second, we iterate from the first
// and last items inwards. If we can afford more, move the first iterator 
// forwards. If we can't afford this much, move the second iterator 
// backwards. Keep track of the most value we can get until the iterators 
// meet.
//
void maxGiftCardValue(vector<pair<string, int>>& items, int giftCard)
{
    string output = "Not possible.";
    if (items.size() <= 1)
    {
        cout << output << endl;
        return;
    }

    int maxValue = 0;
    int frontIdx = 0;
    int backIdx  = items.size() - 1;

    // STL sort using fancy c++11 lambda syntax
    sort(items.begin(), items.end(),
         [](const pair<string, int>& a, const pair<string, int>& b)
         {
             return a.second < b.second;
         });

    while (frontIdx < backIdx)
    {
        int currValue = items[frontIdx].second + items[backIdx].second;
        if (currValue > maxValue &&
            currValue <= giftCard)
        {
            maxValue = currValue;
            output = items[frontIdx].first + " " + 
                     to_string(items[frontIdx].second) + ", " +
                     items[backIdx].first + " " +
                     to_string(items[backIdx].second);
        }

        // If we can afford this, consider a more expensive item for frontIdx.
        // If we can't, then consider a cheaper item for backIdx
        if (currValue <= giftCard)
        {
            frontIdx++;
        }
        else
        {
            backIdx--;
        }
    }

    cout << output << endl;
         
    return;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        cout << "Format:" << endl;
        cout << "<executable> <price file> <gift card total>" << endl;
        exit(1);
    }

    //
    // Boilerplate: read in the price data and store <item, price> pairs
    //

    ifstream inputStream(argv[1]);
    vector<pair<string, int>> items;
    int giftCardTotal = atoi(argv[2]);

    if (!inputStream)
    {
        cout << "Error opening input file. Exiting." << endl;
        exit(1);
    }

    string line;

    while (getline(inputStream, line))
    {
        size_t pos = 0;
        string delimiter = ", ";
        pos = line.find(delimiter);

        string itemName  = line.substr(0, pos);
        string itemPrice = line.substr(pos+delimiter.length(), line.length());

        items.push_back(make_pair(itemName, stoi(itemPrice)));
    }

    maxGiftCardValue(items, giftCardTotal);

    return 0;
}
