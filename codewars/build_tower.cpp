typedef std::string str;
typedef std::vector<str> vecs;

class Kata
{
public:
    vecs towerBuilder(int n)
    {
      vecs res;
      int size = n * 2 - 1;
      for (int stars_start = n - 1; stars_start >= 0; --stars_start) {
        str temp(size, ' ');
        
        for (int j = stars_start; j < n; ++j) {
          temp[j] = '*';
          temp[size - j - 1] = '*';
        }
        
        res.push_back(temp);
      }
      
      return res;
    }
};
