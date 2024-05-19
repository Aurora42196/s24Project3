//
//  Temple.h
//  s24Project3
//
//  Created by Cameron Maiden on 5/19/24.
//

#ifndef Temple_h
#define Temple_h

class Temple
{
public:
        // Constructor/destructor
    Temple(int nRows, int nCols);
    ~Temple();
    
        // Accessors
    int rows() const { return m_rows; };
        // Mutators
    
    
private:
    int m_rows;
    int m_cols;
    
    
};

#endif /* Temple_h */
