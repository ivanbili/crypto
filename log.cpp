#include <gmp.h>
#include <string>
#include <unordered_map>
#include <iostream>
// g++ -o log log.cpp -lgmp -O3

int main()
   {
	 std::unordered_map<std::string, unsigned long int> map;
   mpz_t p, g, g_pwr, h, g_inv, g_pwr_b, left, right;
   mpz_init_set_str (p, "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171", 10);
   mpz_init_set_str (g, "11717829880366207009516117596335367088558084999998952205599979459063929499736583746670572176471460312928594829675428279466566527115212748467589894601965568", 10);
   mpz_init_set_str (h, "3239475104050450443565264378728065788649097520952449527834792452971981976143292558073856937958553180532878928001494706097394108577585732452307673444020333", 10);
   mpz_init (g_inv);
   mpz_invert (g_inv, g, p);
   mpz_init_set(left, h);
   map[mpz_get_str (NULL, 10, left)] = 0;
   for (unsigned long int i = 1; i <= 1048576; i++) // 2^20 = 1048576
      {
      mpz_mul (left, left, g_inv); // g_pwr = g^i
      mpz_mod (left, left, p);
      map[mpz_get_str (NULL, 10, left)] = i;
      }   
   mpz_init_set_ui(right, 1);
   auto got = map.find (mpz_get_str (NULL, 10, right));
   if (got != map.end())
   	  {
   	  std::cout << "Solution: " << got->second <<std::endl; //x0 is zero
   	  return 0;
   	  }
   mpz_init (g_pwr_b);   
   mpz_pow_ui (g_pwr_b, g, 1048576); // g_pwr_b = g^(2^20)
   mpz_mod (g_pwr_b, g_pwr_b, p);
   for (unsigned long int i = 1; i <= 1048576; i++)
      {
      mpz_mul (right, right, g_pwr_b); // g_pwr = g^i
      mpz_mod (right, right, p);
      auto got = map.find (mpz_get_str (NULL, 10, right));
      if (got != map.end())
      	 {
      	 std::cout << "Solution: " << (unsigned long long int) i * 1048576 + got->second <<std::endl;
         return 0;
      	 }
      }
   std::cout << "Solution not found :(" << std::endl; //x0 is zero
   return 0;
   }
