//
// Created by Yusuf Pisan on 4/26/18.
//

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>


#include "skiplist.h"

using namespace std;

// display with level
ostream &operator<<(ostream &Out, const SkipList &SkipL) {
    SkipList::SNode *Curr;
    for (int I = SkipL.Depth - 1; I > -1; I--) {
        Curr = SkipL.FrontGuards[I];
        Out << "Level: " << I << " -- ";
        while (Curr != nullptr) {
            Out << Curr->Data << ", ";
            Curr = Curr->Next;
        }
        Out << endl;
    }
    return Out;
}

//SNode structure constructor
SkipList::SNode::SNode(int Data) : Data{Data}, Next{nullptr}, Prev{nullptr}, UpLevel{nullptr}, DownLevel{nullptr} {}

// default SkipList has Depth of 1, just one doubly-linked list
SkipList::SkipList(int Depth) : Depth{Depth} {
    FrontGuards = new SNode *[Depth];
    RearGuards = new SNode *[Depth];
    for (int I = 0; I < Depth; I++) {
        FrontGuards[I] = new SNode(INT_MIN);
        RearGuards[I] = new SNode(INT_MAX);
    }
    for (int I = 0; I < Depth; I++) {
        if (I != 0) {
            FrontGuards[I]->DownLevel = FrontGuards[I - 1];
            RearGuards[I]->DownLevel = RearGuards[I - 1];
        }
        if (I < Depth - 1) {
            FrontGuards[I]->UpLevel = FrontGuards[I + 1];
            RearGuards[I]->UpLevel = RearGuards[I + 1];
        }
        FrontGuards[I]->Next = RearGuards[I];
        RearGuards[I]->Prev = FrontGuards[I];
    }
}

// return true 50% of time,
// each node has a 50% chance of being at higher level
bool SkipList::alsoHigher() const {
    return rand() % 2 == 1;
}

// return true if successfully added, no duplicates
bool SkipList::add(int Data) {
    int Count = 1;
    auto *NewNode = new SNode(Data);
    SNode *Curr = FrontGuards[0]->Next;
    while (Curr->Next != nullptr && Curr->Data < Data) {
        Curr = Curr->Next;
    }
    if (Data == Curr->Data) {
        delete NewNode;
        return false;
    }
    addBefore(NewNode, Curr);
    while (alsoHigher() && Count < Depth) {
        auto *NewUpper = new SNode(Data);
        NewNode->UpLevel = NewUpper;
        NewUpper->DownLevel = NewNode;
        SNode *BackwardN = NewNode->Prev;
        while (BackwardN->Prev != nullptr && BackwardN->UpLevel == nullptr) {
            BackwardN = BackwardN->Prev;
        }
        BackwardN = BackwardN->UpLevel;
        BackwardN = BackwardN->Next;
        addBefore(NewUpper, BackwardN);
        NewNode = NewUpper;
        Count++;
    }
    return true;
}

// given a SNode, place it before the given NextNode
void SkipList::addBefore(SNode *NewNode, SNode *NextNode) {
    NewNode->Next = NextNode;
    NewNode->Prev = NextNode->Prev;
    NextNode->Prev->Next = NewNode;
    NextNode->Prev = NewNode;
    assert (NewNode->Next == NextNode &&
            NextNode->Prev == NewNode);
    assert (NewNode->Prev != nullptr &&
            NewNode->Prev->Data < NewNode->Data);
}

// destructor
SkipList::~SkipList() {
    // need to delete individual nodes
    SNode *Curr;
    SNode *Temp;
    for (int I = 0; I < Depth; I++) {
        Curr = FrontGuards[I];
        while (Curr != nullptr) {
            Temp = Curr;
            Curr = Curr->Next;
            delete Temp;
        }
    }
    delete[] FrontGuards;
    delete[] RearGuards;
}

// return true if successfully removed
bool SkipList::remove(int Data) {
    SNode *Curr = FrontGuards[Depth - 1];
    SNode *Temp;
    while (Curr != nullptr) {
        if (Curr->Next->Data < Data) {
            Curr = Curr->Next;
        } else if (Curr->Next->Data == Data) {
            Curr = Curr->Next;
            while (Curr != nullptr) {
                Temp = Curr;
                Curr->Next->Prev = Curr->Prev;
                Curr->Prev->Next = Curr->Next;
                Curr = Curr->DownLevel;
                delete Temp;
            }
            return true;
        } else {
            Curr = Curr->DownLevel;
        }
    }
    return false;
}

// return true if found in SkipList
bool SkipList::contains(int Data) {
    SNode *Curr = FrontGuards[Depth - 1];
    while (Curr != nullptr) {
        if (Curr->Next->Data < Data) {
            Curr = Curr->Next;
        } else if (Curr->Next->Data == Data) {
            return true;
        } else {
            Curr = Curr->DownLevel;
        }
    }
    return false;
}
