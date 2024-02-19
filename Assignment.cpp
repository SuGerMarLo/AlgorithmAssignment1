#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class ProductData
{
public:
    int productID;
    float Price;
    string Name, Category;

    ProductData()
    {
        this->productID = 0;
        this->Price = 0.00f;
        this->Name = "N";
        this->Category = "C";
    }

    void SetID(int id)
    {
        this->productID = id;
    }
    void SetPrice(float price)
    {
        this->Price = price;
    }
    void SetName(string name)
    {
        this->Name = name;
    }
    void SetCategory(string category)
    {
        this->Category = category;
    }

    int GetID()
    {
        return this->productID;
    }
    float GetPrice()
    {
        return this->Price;
    }
    string GetName()
    {
        return this->Name;
    }
    string GetCategory()
    {
        return this->Category;
    }
    void InsertProductData(int id, float price, string name, string category)
    {
        SetID(id);
        SetPrice(price);
        SetName(name);
        SetCategory(category);
    }
};

class Node
{
public:
    ProductData data;
    Node* next;
    Node* prev;

    Node()
    {
        this->next = nullptr;
        this->prev = nullptr;
    }

    void InsertNode(ProductData data)
    {
        if (this->data.Name == "N")
        {
            SetData(data);
            return;
        }

        if (next != nullptr)
        {
            next->InsertNode(data);
        }
        else
        {
            Node* newNode = new Node();
            newNode->SetData(data);
            this->next = newNode;
            newNode->prev = this;
        }

    }
    void SetData(ProductData data)
    {
        this->data = data;
    }

    Node* Search(int id)
    {
        if (this->data.productID == id)
        {
            return this;
        }
        else if (next == nullptr)
        {
            return nullptr;
        }
        else
        {
            return next->Search(id);
        }
    }

    Node* GetIndex(int index)
    {
        Node* first = prev;
        if (first == nullptr) 
        {
            first = this;
        }
        while (first->prev != nullptr)
        {
            first = first->prev;
        }
        for (int i = 0; i < index; i++)
        {
            if (first == nullptr)
            {
                return nullptr;
            }
            first = first->next;
        }
        return first;

    }

    void NodeDelete(int id)
    {
        Node* delNode;
        delNode = Search(id);
        if (delNode != nullptr)
        {
            delNode->prev->next = delNode->next;
            delNode->next->prev = delNode->prev;
            delete(delNode);
        }
        else
        {
            cout << "\nError: ID not found in index\n";
        }
    }

    void Update(int id, ProductData data)
    {
        Node* updateNode;
        updateNode = Search(id);
        if (updateNode != nullptr)
        {
            updateNode->SetData(data);
        }
        else
        {
            cout << "\nError: ID not found in index\n";
        }

    }

    int count()
    {
        if (next == nullptr)
        {
            return 1;
        }
        else
        {
            return 1 + next->count();
        }
    }

};


vector<string> split(string s, string delimiter) 
{
    size_t start = 0, end, delimiter_length = delimiter.length();
    string token;
    vector<string> res;

    while ((end = s.find(delimiter, start)) != string::npos) 
    {
        token = s.substr(start, end - start);
        start = end + delimiter_length;
        res.push_back(token);
    }

    res.push_back(s.substr(start));
    return res;
}

void BubbleSort(Node* start)
{
    ProductData data;
    for (int i = 0; i < start->count(); i++)
    {
        for (int j = 0; j < start->count() - i; j++)
        {
            Node* currentNode;
            Node* next;
            currentNode = start->GetIndex(j);
            next = start->GetIndex(j + 1);
            data = currentNode->data;

            if (next != nullptr)
            {
                if (currentNode->data.GetID() > next->data.GetID())
                {
                    currentNode->data = next->data;
                    next->data = data;
                }
            }

        }
    }
}


int main()
{
    ProductData currentData;
    string line, id, price, name, category, delimiter = ", ";

    Node* head = new Node();

    fstream datafile;
    datafile.open("product_data.txt");

    if (datafile.is_open())
    {
        while (getline(datafile, line))
        {
            vector<string> v = split(line, delimiter);
            currentData.InsertProductData(stoi(v[0]), stof(v[2]), v[1], v[3]);
            head->InsertNode(currentData);
        }
        datafile.close();
    }
    else cout << "Error: Cannot open file";

    BubbleSort(head);
    for (int i = 0; i < head->count(); i++)
    {
        cout << head->GetIndex(i)->data.GetID() << endl;
    }
}