#pragma once

/*
MIT License

Copyright (c) 2018 harismuneer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

template <class T>
struct ListItem
{
    T value;                //Data Item
    ListItem<T>* next;     //Pointer to the next item of the List
    ListItem<T>* previous; //Pointer to the previous item of the list

    T& getValue()           //I know the encapsulation is being violated here :/
    {
        return value;
    }
};



template <class T>
class List
{

private:
    ListItem<T>* head;
    ListItem<T>* tail;

public:

    List()
    {
        head = tail = NULL;
    }

    List(const List<T>& otherList)
    {
        //If the other list is empty then make the current list empty too.
        if (otherList.head == NULL) {
            head = NULL;
        }

        //If the other List isn't empty:
        else {
            ListItem<T>* current1 = otherList.head;  //current1 points to the other list.

            head = tail = new ListItem<T>;
            head->previous = NULL;

            head->value = current1->value;


            current1 = current1->next;

            if (current1 == NULL)
                head->next = NULL;

            else {
                ListItem<T>* current2 = head;    //current2 keeps track of the list being created.

                while (current1 != NULL) {
                    current2->next = new ListItem<T>;
                    current2->next->previous = current2;
                    current2 = current2->next;

                    current2->value = current1->value;
                    current1 = current1->next;
                }

                current2->next = NULL;
                tail = current2;
            }
        }

    }

    List<T> operator = (const List<T>& otherList)
    {
        if (&otherList != this) {
            if (head != NULL)                   //If list isn't empty then delete the whole list.
            {
                ListItem<T>* current = head;

                while (current != NULL) {
                    ListItem<T>* temp = current;
                    current = current->next;
                    delete temp;
                }

                head = tail = NULL;
            }

            //If the other list is empty then make the current list empty too.
            if (otherList.head == NULL) {
                head = NULL;
            }

            //If the other List isn't empty:
            else {
                ListItem<T>* current1 = otherList.head;  //current1 points to the other list.

                head = tail = new ListItem<T>;
                head->previous = NULL;

                head->value = current1->value;


                current1 = current1->next;

                if (current1 == NULL)
                    head->next = NULL;

                else {
                    ListItem<T>* current2 = head;    //current2 keeps track of the list being created.

                    while (current1 != NULL) {
                        current2->next = new ListItem<T>;
                        current2->next->previous = current2;
                        current2 = current2->next;

                        current2->value = current1->value;
                        current1 = current1->next;
                    }

                    current2->next = NULL;
                    tail = current2;
                }
            }

        }

        return *this;
    }


    ~List()
    {
        if (head != NULL)                   //If list is empty then do nothing.
        {
            ListItem<T>* current = head;

            while (current != NULL) {
                ListItem<T>* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    void insertAtHead(T item)
    {
        ListItem<T>* temp = new ListItem<T>;
        temp->value = item;

        temp->next = head;
        temp->previous = NULL;

        if (head != NULL)
            temp->next->previous = temp;
        else
            tail = temp;

        head = temp;
    }

    void insertAtTail(T item)
    {
        ListItem<T>* temp = new ListItem<T>;
        temp->value = item;

        temp->previous = tail;
        temp->next = NULL;

        if (tail != NULL)
            temp->previous->next = temp;
        else
            head = temp;

        tail = temp;
    }

    ListItem<T>* getHead()
    {
        return head;
    }

    ListItem<T>* getTail()
    {
        return tail;
    }

    ListItem<T>* searchForL(T item)
    {
        if (head == NULL)                //If the list is empty
        {
            return NULL;
        }

        else if (item > tail->value) {
            return NULL;
        }

        else {
            ListItem<T>* current = head;

            while (current != NULL && current->value <= item) {
                if (current->value == item) {
                    return current;
                }

                current = current->next;
            }

            return NULL;
        }
    }

    void deleteElement(T& item)
    {
        if (head != NULL) //If the list isn't empty.
        {
            ListItem<T>* current = head;

            while (current->next != NULL && current->value < item) {
                current = current->next;
            }


            //If the element is found.
            if (current->value == item) {
                if (current == head) {
                    head = head->next;

                    if (head == NULL)
                        tail = NULL;
                    else
                        head->previous = NULL;
                }

                else {
                    current->previous->next = current->next;

                    if (current->next != NULL)
                        current->next->previous = current->previous;
                    else
                        tail = current->previous;
                }

                delete current;
            }
        }
    }

    void deleteHead()
    {
        if (head != NULL) {
            ListItem<T>* temp = head->next;
            delete head;
            head = temp;

            if (head == NULL)
                tail = NULL;

            else
                head->previous = NULL;
        }
    }

    void deleteTail()
    {
        if (head != NULL) {
            ListItem<T>* temp = tail->previous;
            delete tail;
            tail = temp;

            if (tail == NULL)
                head = NULL;

            else
                tail->next = NULL;
        }
    }

    void deleteNode(ListItem<T>* node)
    {
        if (node == head) {
            head = head->next;
        }

        else if (node == tail) {
            tail = tail->previous;
        }

        else {
            node->previous->next = node->next;
            node->next->previous = node->previous;
        }

        if (head != NULL) {
            head->previous = NULL;
            tail->next = NULL;
        }

        else
            tail = NULL;

        delete node;
    }


    int length()
    {
        int length = 0;
        ListItem<T>* current = head;

        while (current != NULL) {
            length++;
            current = current->next;
        }

        return length;
    }


    ListItem<T>* getDesiredElement(int n)
    {
        ListItem<T>* current = head;

        if (n <= length()) {
            while (n != 0) {
                current = current->next;
                n--;
            }
        }

        return current;
    }
};