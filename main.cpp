#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int GCD(int a, int b)
{
    if ((a == 0) || (b == 0))
    {
        return 1;
    }

    if (a == b)
    {
        return a;
    }

    if (a < b)
    {
        std::swap(a, b);
    }

    a = a - b;

    return GCD(a, b);
}

int FindFactors(int n)
{
    int p = 0;
    for (unsigned int i = 2; i < n; i++)
    {
        if (GCD(i, n) == i)
        {
            if (GCD(i, (n / i) == 1))
            {
                return i;
            }
        }
    }
    return -1;
}

int moduloInverse(int a, int m) {
    int i = 1;
    int j = 1;
    while ((a * i) % ((m * j) + 1) != 0) {
        if ((a * i) > (m * j)) {
          j++;
        } else {
          i++;
        }
    }
    cout << "d is " << i << endl;
    return i;
}

int main()
{
  std::ifstream ifST;
  std::ofstream output("output.txt");

  int e, n;
  std::cout << "enter e: " << std::endl;
  std::cin >> e;
  std::cout << "enter n: " << std::endl;
  std::cin >> n;

  int p, q;
  p = FindFactors(n);
  q = n / p;

  char input = '0';
  while ((input != 'e') && (input != 'd'))
  {
      std::cout << "encrypting or decrypting? (e/d)" << std::endl;
      std::cin >> input;
  }

  unsigned int i;
  unsigned long long m;
  
  switch(input) {
    case 'd': //decrypt 
      {
        ifST.open("DecryptMe.txt");
        int tempint;
        std::vector<unsigned int> M;

        while (ifST >> tempint)
        {
            M.push_back(tempint);
        }
        ifST.close();
          int PhiN = (p - 1) * (q - 1);
          int d;
          d = moduloInverse(e, PhiN);
          for (i = 0; i < M.size(); i++)
          {
              m = M.at(i);
              m = pow(m, d);
              m = m % n;

              if ((m > 1) && (m < 28))
              {
                  m += 63;
                  output << char(m);
                  std::cout << char(m);
              }
              else if (m == 28)
              {
                  output << " ";
                  std::cout << " ";
              }
          }
          
          std::cout << std::endl;

          std::cout << "done!" << std::endl;
        break;
      }
    case 'e': //encrypt
      {
        
        ifST.open("EncryptMe.txt");
        char tempchar;
        std::vector<char> L;

        while (ifST >> tempchar)
        {
          L.push_back(tempchar-63);  
          if( ifST.peek() == ' '){
            L.push_back(28);
          }

        }
        ifST.close();


        int tempm;
        int j;
        for(i = 0; i < L.size(); i++){
          m = (int)L.at(i);
          tempm = m;
          for (j = 1; j < e; j++) {
            tempm = m * tempm;
            tempm = tempm % n;  
          }
          m = tempm;
          output << m << " ";
          std::cout << m << " ";
        }
        std::cout << std::endl <<  "done!" << std::endl;
        break; 
      }
  }
  return 0;
}