// stl-map-example.cc
// příklad použití STL kontejneru map<>
// program počítá četnost slov ve vstupním textu
// slovo je cokoli oddělené "bílým znakem" === isspace

// Note: created by Petr Peringer (peringer@fit.vutbr.cz)

#include <string>
#include <iostream>
#if 1       // zkuste si i variantu s 0
# include <tr1/unordered_map>
  typedef std::tr1::unordered_map<std::string,int>  map_t;
#else
# include <map>
  typedef std::map<std::string,int>  map_t;
#endif
typedef map_t::iterator            mapiter_t;

int main() {
  std::string word;
  map_t m; // asociativní pole - indexem je slovo

  while( std::cin >> word )  // čtení slova
    m[word]++;               // počítání výskytů slova

  // tisk
  for(mapiter_t i=m.begin(); i!=m.end(); ++i)
    std::cout << i->first <<"\t"<< i->second <<"\n";
  //             slovo (klíč)         počet (data)
}
