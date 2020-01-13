#include "UniqueArray.h"
// Created by jonathan_pc on 1/12/2020.

#ifndef MTM3_UNIQUEARRAYIMP_H

#include "UniqueArray.h"

//**********************************************************************
template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size):
        array_size(size), num_of_element(0)
{

    array = new Element*[array_size];

    for (int i=0; i<array_size; i++){

        array[i] = nullptr;
    }

}

//**********************************************************************
template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray &other) {

    array_size = other.array_size;
    num_of_element = other.num_of_element;
    array=new Element*[array_size];


    for (int i=0; i<other.array_size; i++)
    {
        array[i] = new Element(*other.array[i]);
    }

}

//**********************************************************************
template<class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray() {
    for(int i=0; i<array_size;i++)
    {
        delete array[i];
    }
    delete [] array;
}

//**********************************************************************
template<class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element &element,
                                             unsigned int &index) const {
    Compare c;

    for(int i = 0; i < array_size; i++)
    {
        if(array[i] != nullptr) {

            if (c(element, *array[i])) {
                index = i;

                return true;
            }

        }

    }
    return false;
}

//**********************************************************************


template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element &element) {

    unsigned int *int_ptr;
    if (array_size == num_of_element)
    {
        throw UniqueArrayIsFullException();
    }

    if(getIndex(element,*int_ptr))
    {
        return *int_ptr;
    }
    for(int i=0; i<array_size; i++)
    {
        if(array[i] == nullptr)
        {
            array[i] = new Element(element);

            num_of_element++;

            return i;
        }
    }

    return 0;

}


//**********************************************************************
template<class Element, class Compare>
const Element *
UniqueArray<Element, Compare>::operator[](const Element &element) const {
    unsigned int* int_ptr;
    if(getIndex(element, *int_ptr))
    {
        return array[*int_ptr];
    }
    return nullptr;
}




//**********************************************************************
template<class Element, class Compare>
bool UniqueArray<Element, Compare>::remove(const Element &element) {

    unsigned int* int_ptr;
    if(getIndex(element,*int_ptr))
    {
        delete array[*int_ptr];

        array[*int_ptr] = nullptr;

        num_of_element--;

        return true;
    }
    return false;
}



//**********************************************************************

template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getCount() const {

    return num_of_element;
}


//**********************************************************************
template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getSize() const {

    return array_size;
}




//**********************************************************************
template<class Element, class Compare>
UniqueArray<Element, Compare> UniqueArray<Element, Compare>::filter
(const UniqueArray::Filter &f) const {

    UniqueArray<Element,Compare> new_array(array_size);


    for(int i=0; i<array_size; i++)
    {
        if(f(*array[i]))

            new_array.array[i]=array[i];
    }

    return new_array;
}

#endif //MTM3_UNIQUEARRAYIMP_H
