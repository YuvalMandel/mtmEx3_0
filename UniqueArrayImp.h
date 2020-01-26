// Created by jonathan_pc on 1/12/2020.
#ifndef MTM3_UNIQUEARRAYIMP_H

//**********************************************************************
template<class Element, class Compare>
/**
 * UniqueArray constructor
 *
 * creates array of pointers to Elements. dynamic allocation occurs only
 * when an element is received.
 */
UniqueArray<Element, Compare>::UniqueArray(unsigned int size):
        array_size(size), num_of_element(0)
{

    array = new Element*[array_size];

    for (unsigned int i = 0; i < array_size; i++){

        array[i] = nullptr;

    }

}

//**********************************************************************
template<class Element, class Compare>

/**
* UniqueArray copy constructor
*
* creates array of pointers to Elements. for each element, use the element
 * copy C'tor to create a new copied Element.
*/
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray &other) {

    array_size = other.array_size;
    num_of_element = other.num_of_element;
    array=new Element*[array_size];

    for (unsigned int i=0; i<other.array_size; i++)
    {
        if (other.array[i]!= nullptr) {
            array[i] = new Element(*other.array[i]);
        }
        else{
            array[i]= nullptr;
        }
    }

}

//**********************************************************************
template<class Element, class Compare>


/**
* UniqueArray copy D'tor
*
*/
UniqueArray<Element, Compare>::~UniqueArray() {

    for(unsigned int i = 0; i <array_size; i++)
    {
        if(array[i] != nullptr){

            delete array[i];

        }
    }

    delete[] array;

}

//**********************************************************************
template<class Element, class Compare>


/**
* returns true if an element is in the array. false otherwise. uses type:
 * Compare to decide whether two elements are in fact equal. if equality is
 * found the index of the item in the array is returned in param "index".
*/
bool UniqueArray<Element, Compare>::getIndex(const Element &element,
                                             unsigned int &index) const {
    Compare c;

    for(unsigned int i = 0; i < array_size; i++)
    {
        if(array[i] != nullptr){

            if (c(element, *array[i])) {

                index = i;

                return true;

            }

        }

    }

    return false;
    
}

//**********************************************************************
/**
* inserts an item to the array if it does not already exist there.
*/
template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element &element) {

    unsigned int int_temp;
    
    if(getIndex(element,int_temp)) return int_temp;

    if (array_size == num_of_element) throw UniqueArrayIsFullException();

    for(int unsigned i = 0; i < array_size; i++)
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
/**
*if the element received it equal to an element in the array (equal defined
 * by Compare) a pointer to  the element in the array is returned.
*/
const Element *
UniqueArray<Element, Compare>::operator[](const Element &element) const {

    unsigned int temp_int = 0;

    if(getIndex(element, temp_int))
    {
        return array[temp_int];
    }

    return nullptr;
}

//**********************************************************************
template<class Element, class Compare>
/**
*if the element exists in the array it is removed. true or false returned to
 * indicate the successful removal of element.
*/
bool UniqueArray<Element, Compare>::remove(const Element &element) {

    unsigned int int_temp;

    if(getIndex(element,int_temp))
    {
        delete array[int_temp];

        array[int_temp] = nullptr;

        num_of_element--;

        return true;
    }

    return false;

}

//**********************************************************************
template<class Element, class Compare>
/**
*returnes current amount of elements stored in array
*/
unsigned int UniqueArray<Element, Compare>::getCount() const {

    return num_of_element;

}


//**********************************************************************
template<class Element, class Compare>
/**
*returns the maximum number of items that can be stored in array.
*/
unsigned int UniqueArray<Element, Compare>::getSize() const {

    return array_size;

}




//**********************************************************************
template<class Element, class Compare>
/**
 * creates a new  Unique array containing only the a elements of the current
 * array that when given to funtion: filter, return true.  the index of these
 * items in the new filtered array is identical to their index in the
 * original array.
*/
UniqueArray<Element, Compare> UniqueArray<Element, Compare>::filter
(const UniqueArray::Filter &f) const {

    UniqueArray<Element,Compare> new_array(array_size);

    for(int unsigned i=0; i<array_size; i++)
    {
        if(f(*array[i])) {

            new_array.array[i] = new Element;

            *new_array.array[i] = *array[i];

            new_array.num_of_element++;

        }

    }

    return new_array;

}

//**********************************************************************
template<class Element, class Compare>
/**
*returnes a pointer to the element in index: "index" if the array.
*/
Element *UniqueArray<Element, Compare>::getElementByIndex(int index) const {

    return array[index];

}

#endif //MTM3_UNIQUEARRAYIMP_H
