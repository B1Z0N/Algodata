#include <bits/stdc++.h>

using namespace std;

template<typename K, typename V = int>
class trie
{
    public:

    trie() : flag(false)
    {}

    bool has( const K &collection ) const {
        for( const auto &it : children ) {
            if( it.second.has(collection) ) {
                return true;
            }
        }
        return flag && collection == branch ? true : false;
    }

    V& insert( const K &collection ) {
        trie *node = this;
        for( auto &c : collection ) {
            auto found = node->children.find( c );
            if( found == node->children.end() ) {
                auto copy = node->branch;
                std::back_inserter( copy ) = c;
                node->children[c] = trie( copy );
            }
            node = &(node->children[c]);
        }
        node->flag = true;
        return node->leaf;
    }

    V& operator[]( const K &collection ) {
        return insert( collection );
    }

    std::vector<const K *> list() const {
        std::vector<const K *> results;
        if( flag ) {
            results.push_back( &branch );
        }
        for( const auto &it : children ) {
            auto keys = it.second.list();
            for( const auto &key : keys ) {
                results.push_back( key );
            }
        }
        return results;
    }

    std::vector<const K *> complete( const K &prefix ) const {
        const trie *node = this;
        for( auto &elem : prefix ) {
            const auto found = node->children.find( elem );
            if( found == node->children.end() ) {
                return std::vector<const K *>();
            }
            node = &found->second;
        }
        return node->list();
    }

	int count( const K &prefix ) const {
			const trie *node = this;
			for ( auto &elem : prefix ) {
				const auto found = node->children.find( elem );
				if ( found == node->children.end() ) {
						return 0;
				}
				node = &found->second;
			}

			return node->res_num();
	}

private:

	int res_num() const {
			int sum = flag ? 1 : 0;
	        for( const auto &it : children ) {
    	        sum += it.second.res_num();
	        }
			return sum;	
	}
public:

    unsigned size() const {
        return list().size();
    }

    protected:

    trie( const K &branch ) : branch(branch), flag(false)
    {}

    K branch;
    V leaf;
    bool flag;
    std::map< typename K::value_type, trie > children;
};


/*
 * Complete the contacts function below.
 */
vector<int> contacts(vector<pair<string, string>> queries) {
    /*
     * Write your code here.
     */
	trie<string> t;
	vector<int> occurences;
	for (const auto &q : queries) {
		if (q.first == "add") {
			t.insert(q.second);
		} else {
			occurences.push_back(t.count(q.second));
		}
	}
    
    return occurences;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int queries_rows;
    cin >> queries_rows;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<pair<string, string>> queries(queries_rows);
    for (int queries_row_itr = 0; queries_row_itr < queries_rows; queries_row_itr++) {
        cin >> queries[queries_row_itr].first >> queries[queries_row_itr].second;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> result = contacts(queries);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];
        cout << result[result_itr];
        if (result_itr != result.size() - 1) {
            fout << "\n";
            cout << "\n";
        }
    }


    fout << "\n";
    cout << "\n";
    fout.close();

    return 0;
}

