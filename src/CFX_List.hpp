////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016 Custom FX. All right reserved.
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
// The Custom FX library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// The Custom FX library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
// for more details.
//
// You should have received a copy of the GNU General Public License along with
// The Custom FX library. If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef CFX_List_h
#define CFX_List_h

template<class T>
struct CFX_ListNode
{
  T data;
  CFX_ListNode *pnext;
};

template <typename T>
class CFX_List
{
  public:
    CFX_List();
    ~CFX_List();
    virtual unsigned int Size() const;
    virtual void Add(T data);
    virtual T Get(unsigned int index);
  protected:
  private:
    int m_size;
    CFX_ListNode<T>* m_first;
    CFX_ListNode<T>* m_last;
    unsigned int m_lastIndex;
    CFX_ListNode<T>* m_lastNode;
};

template <typename T>
CFX_List<T>::CFX_List()
{
  m_first = NULL;
  m_last = NULL;
  m_size = 0;
  m_lastIndex = 0;
  m_lastNode = 0;
}

template <typename T>
CFX_List<T>::~CFX_List()
{
  CFX_ListNode<T>* temp;
  while (m_first)
  {
    temp = m_first;
    m_first = m_first->pnext;
    delete temp;
  }
  m_last = NULL;
  m_size = 0;
  m_lastIndex = 0;
}

template <typename T>
unsigned int CFX_List<T>::Size() const
{
  return m_size;
}

template <typename T>
void CFX_List<T>::Add(T data)
{
  CFX_ListNode<T>* newnode = new CFX_ListNode<T>();
  newnode->pnext = NULL;
  newnode->data = data;
  if (m_first)
  {
    m_last->pnext = newnode;
    m_last = newnode;
  }
  else
  {
    m_first = newnode;
    m_last = newnode;
  }
  m_size++;
  m_lastIndex = 0;
  m_lastNode = m_first;
}

template <typename T>
T CFX_List<T>::Get(unsigned int index)
{
  CFX_ListNode<T>* node;
  unsigned int position;

  if (m_lastIndex != 0 && m_lastIndex <= index)
  {
    position = m_lastIndex;
    node = m_lastNode;
  }
  else
  {
    position = 0;
    node = m_first;
  }
  
  while ((position < index) && node)
  {
    position++;
    node = node->pnext;
  }
  
  if (node)
  {
    m_lastIndex = position;
    m_lastNode = node;
    return node->data;
  }
  else
  {
    m_lastIndex = 0;
    m_lastNode = m_first;
    return T();
  }
}

#endif // CFX_List_h
