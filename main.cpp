#include <iostream>
#include <limits>
using namespace std;

const int MinItems = 10;
const int Maxbids = 100;
struct Item 
{
    int itemNumber;
    string description;
    double reservePrice;
    int numberOfBids;
    double highestBid;
};
struct Bid 
{
    int buyerNumber;
    int itemNumber;
    double bidAmount;
};
int getNumberOfItems();
void auctionSetup(Item items[], int numItems);
void displayItems(const Item items[], int numItems);
void recordBid(Item items[], Bid bids[], int& numBids, int numItems);
void endAuction(const Item items[], const Bid bids[], int numBids, int numItems);

int main() 
{
    int numItems = getNumberOfItems();
    Item items[numItems];
    Bid bids[Maxbids];
    int numBids = 0;

    auctionSetup(items, numItems);
    recordBid(items, bids, numBids, numItems);
    endAuction(items, bids, numBids, numItems);

    return 0;
}


int getNumberOfItems() 
{
    int numItems;
    do {
        cout << "Enter the number of items for the auction (should be at least 10): ";
        cin >> numItems;

        if (numItems < MinItems) 
        {
            cout << "Error: Number of items should be at least 10. Please try again.\n";
        }
    } while (numItems < MinItems);

    return numItems;
}

void auctionSetup(Item items[], int numItems) 
{
    cout << "Auction set up\n";
    for (int i = 0; i < numItems; ++i) 
    {
        Item newItem;
        cout << "Enter details for item #" << i + 1 << ":\n";
        newItem.itemNumber = i + 1;
        
        cout << "Description: ";
        cin.ignore();
        getline(cin, newItem.description);

        cout << "Reserve price: ";
        cin >> newItem.reservePrice;

        newItem.numberOfBids = 0;

        newItem.highestBid = 0;

        items[i] = newItem;
    }

    cout << "Auction set up successfully!\n\n";
}

void displayItems(const Item items[], int numItems) 
{
    cout << "Item Number\tDescription\tReserve Price\tCurrent Highest Bid\n";
    for (int i = 0; i < numItems; ++i) 
    {
        cout << items[i].itemNumber << "\t\t" << items[i].description << "\t\t$" << items[i].reservePrice << "\t\t$" << items[i].highestBid << endl;
    }
}

void recordBid(Item items[], Bid bids[], int& numBids, int numItems) 
{
    cout << "Buyer bids\n";
    int buyerNumber;
    int itemNumber;
    double bidAmount;
    char continueBidding;
    
    do {
        displayItems(items, numItems);
        cout << "Enter your buyer number: ";
        cin >> buyerNumber;
        cout << "Enter the item number you want to bid for: ";
        cin >> itemNumber;
        cout << "Enter your bid amount: $";
        cin >> bidAmount;
        
        if (bidAmount <= items[numItems - 1].highestBid) 
        {
             cout << "Error: Your bid must be higher than the current highest bid.\n";
        } 
        else
        {
            items[itemNumber - 1].numberOfBids++;
            items[itemNumber - 1].highestBid = bidAmount;

            Bid newBid{buyerNumber, itemNumber, bidAmount};
            bids[numBids++] = newBid;

            cout << "Bid recorded successfully!\n";
        }

        cout << "Do you want to place another bid? (y/n): ";
        cin >> continueBidding;
    } while (continueBidding == 'y' || continueBidding == 'Y');

    cout << "\n";
}

void endAuction(const Item items[], const Bid bids[], int numBids, int numItems) 
{
    cout << "At the end of the auction\n";

    double totalFee = 0.0;
    int itemsSold = 0;
    int itemsNotMeetingReserve = 0;
    int itemsWithNoBids = 0;

    cout << "Results:\n";
    for (int i = 0; i < numItems; ++i) 
    {
        if (items[i].numberOfBids > 0) 
        {
            if (items[i].highestBid >= items[i].reservePrice) 
            {
                totalFee += 0.1 * items[i].highestBid;
                itemsSold++;
                cout << "Item #" << items[i].itemNumber << " - Sold for $" << items[i].highestBid << " (Fee: $" << 0.1 * items[i].highestBid << ")\n";
            } 
            else 
            {
                itemsNotMeetingReserve++;
                cout << "Item #" << items[i].itemNumber << " - Did not meet reserve price. Current highest bid: $" << items[i].highestBid << "\n";
            }
        } 
        else 
        {
            itemsWithNoBids++;
            cout << "Item #" << items[i].itemNumber << " - No bids received.\n";
        }
    }

    cout << "\nSummary:\n";
    cout << "Total fee for sold items: $" << totalFee << "\n";
    cout << "Number of items sold: " << itemsSold << "\n";
    cout << "Number of items not meeting reserve price: " << itemsNotMeetingReserve << "\n";
    cout << "Number of items with no bids: " << itemsWithNoBids << "\n";
}

