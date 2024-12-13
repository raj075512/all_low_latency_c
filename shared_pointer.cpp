#include<iostream>

using namespace std;


template<typename T>
class SharedPointer
{
  T *ptr;
  size_t* counter;
  
  public:
  
  void release()
  {
      if(counter)
      {
         if(--(*counter)==0)
          {
              delete counter;
              delete ptr;
              ptr=NULL;
              counter=NULL;
          }
      }
  }
  
  //default constr//
  
  SharedPointer():ptr(NULL),counter(NULL)
  {
      
  }
  
  // parameterized constr 
    SharedPointer(T *p):ptr(p),counter(new size_t(1))
    {}
    
    // destr//
    
    ~SharedPointer()
    {
        release();
    }
    
    // copy constr//
    SharedPointer (const SharedPointer &other):ptr(other.ptr),counter(other.counter)
    {
      if(counter)
      (*counter)++;
    }
    
    // copy assignment oprte//
    
    SharedPointer & operator=(const SharedPointer &other) noexcept 
    {
        if(this==&other)
        return *this;
        
        release();
        ptr=other.ptr;
        counter=other.counter;
        if(counter)
        ++(*counter);
        return *this;
        
        
    }
    
    // move constr//
    SharedPointer ( SharedPointer &&other)noexcept:ptr(other.ptr),counter(other.counter)
    {
     
     
     other.ptr=NULL;
     other.counter=NULL;
     
     
    }
    
    // move assignmet oprtr//
    SharedPointer & operator=(SharedPointer && other) noexcept
    {
        if(this==&other)
        {
            return *this;
        }
        
        release();
        ptr=other.ptr;
        counter=other.counter;
       
        other.ptr=NULL;
        other.counter=NULL;
        return *this;
        
        
    }
    
    T *get()const
    {
        return ptr;
    }
     
    //  overloading dereferencing 
    T & operator*()const
    {
        return *ptr;
    }
    
    // overlloading row pointer
    T * operator->()const{
        return ptr;
    }
    
    size_t use_count()const {
        return counter?*counter:0;
    }
    
    void reset(T *p)
    {
        release();
        if(p)
        {ptr=p;
        counter=new size_t(1);
          
            
        }else{
            ptr=NULL;
            counter=NULL;
        }
        
    }
    
    
};


int main() {
    // Example usage of SharedPointer
    {
        SharedPointer<int> sp1(new int(10));  // Create shared pointer
        std::cout << "sp1 use count: " << sp1.use_count() << "\n";

        SharedPointer<int> sp2 = sp1;  // Copy shared pointer
        std::cout << "sp1 use count: " << sp1.use_count() << "\n";
        std::cout << "sp2 use count: " << sp2.use_count() << "\n";

        SharedPointer<int> sp3 = std::move(sp1);  // Move shared pointer
        std::cout << "sp1 use count: " << sp1.use_count() << "\n";
        std::cout << "sp3 use count: " << sp3.use_count() << "\n";

        sp3.reset(new int(20));  // Reset shared pointer
        std::cout << "sp3 use count: " << sp3.use_count() << "\n";
    }  // All resources should be cleaned up here

    return 0;
}
