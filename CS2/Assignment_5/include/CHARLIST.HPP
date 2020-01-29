/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 5
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 3.2.2018
Purpose: The purpose of this program is to display the skills that we learned about lists.
*/

#ifndef CHARLIST_HPP_INCLUDED
#define CHARLIST_HPP_INCLUDED

class charList
{

public:
    charList(){ head = nullptr; };
    void appendNode(char);
    void insertNode(char);
    void deleteNode(char);
    void displayList() const;
    ~charList();

private:
    struct ListNode
    {
        char value;
        ListNode* next;
    };
    ListNode* head;
};


#endif // CHARLIST_HPP_INCLUDED
