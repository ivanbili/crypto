#include <gmp.h>
#include <string>
#include <string.h>
#include <unordered_map>
#include <iostream>
// g++ -o log rsa.cpp -lgmp -O3

int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

int main()
   {
   //std::unordered_map<std::string, unsigned long int> map;
   mpz_t N, A, A_squared, x, p, q, check, i1, i2, i1_squared, N_24;
   std::cout << std::endl << "Question1:" << std::endl;
   mpz_init_set_str (N, "179769313486231590772930519078902473361797697894230657273430081157732675805505620686985379449212982959585501387537164015710139858647833778606925583497541085196591615128057575940752635007475935288710823649949940771895617054361149474865046711015101563940680527540071584560878577663743040086340742855278549092581", 10);
   std::cout << " N:       " << mpz_get_str (NULL, 10, N) << std::endl;
   mpz_init (A);
   mpz_sqrt(A, N); mpz_add_ui(A, A, 1);
   mpz_init (A_squared);
   mpz_powm_ui(A_squared, A, 2, N);
   mpz_init(x);
   mpz_sub(x, A_squared, N); mpz_mmod(x, x, N); mpz_sqrt(x, x);
   mpz_init (p);
   mpz_sub(p, A, x);
   mpz_init (q);
   mpz_add(q, A, x);
   std::cout << " p:       " << mpz_get_str (NULL, 10, p) << std::endl;
   std::cout << " q:       " << mpz_get_str (NULL, 10, q) << std::endl;
   mpz_init (check);
   mpz_mul(check, p, q);
   std::cout << " check:   " << mpz_get_str (NULL, 10, check) << std::endl;
   std::cout << " smaller: " << mpz_get_str (NULL, 10, mpz_cmp(p, q) > 0 ? q : p) << std::endl;
   	
   std::cout << std::endl << "Question4:" << std::endl;
   mpz_t e, d, phi, cipher, plain;
   mpz_init_set_str (e, "65537", 10);
   mpz_init_set_str (cipher, "22096451867410381776306561134883418017410069787892831071731839143676135600120538004282329650473509424343946219751512256465839967942889460764542040581564748988013734864120452325229320176487916666402997509188729971690526083222067771600019329260870009579993724077458967773697817571267229951148662959627934791540", 10);
   mpz_init (phi);
   mpz_sub(phi, N, p); mpz_sub(phi, phi, q); mpz_add_ui(phi, phi, 1);
   mpz_init (d);
   mpz_invert(d , e, phi);
   mpz_mul(check, d, e); mpz_mmod(check, check, phi);
   std::cout << " e:       " << mpz_get_str (NULL, 10, e) << std::endl;
   std::cout << " d:       " << mpz_get_str (NULL, 10, d) << std::endl;
   std::cout << " check:   " << mpz_get_str (NULL, 10, check) << std::endl;
   mpz_init (plain);
   mpz_powm(plain, cipher, d, N);

   char * str = mpz_get_str(NULL, 16, plain);
   std::cout << " plain:   " << mpz_get_str (NULL, 10, plain) << std::endl;
   for (int i = 0; i < strlen(str); i++)
      {
      if (str[i] == '0' && str[i+1] == '0')
         {
         int a = 0;
         for (int j = i+2; j < strlen(str); j+=2)
            {
            str[a] = hex2int(str[j])*16 + hex2int(str[j+1]);
            a++;
            }
         str[a] = 0;
         break;
         }	
      }
   std::cout << " decoded: " << str << std::endl;
   free(str);   	
   std::cout << std::endl << "Question2:" << std::endl;
   mpz_set_str(N, "648455842808071669662824265346772278726343720706976263060439070378797308618081116462714015276061417569195587321840254520655424906719892428844841839353281972988531310511738648965962582821502504990264452100885281673303711142296421027840289307657458645233683357077834689715838646088239640236866252211790085787877", 10);
   std::cout << " N:       " << mpz_get_str (NULL, 10, N) << std::endl;
   mpz_set_str(check, "0", 10);
   mpz_sqrt(A, N); mpz_add_ui(A, A, 1);
   while (mpz_cmp(check, N) != 0)
      {
      mpz_add_ui(A, A, 1);
      mpz_powm_ui(A_squared, A, 2, N);
      mpz_sub(x, A_squared, N); mpz_mmod(x, x, N); mpz_sqrt(x, x);
      mpz_sub(p, A, x);
      mpz_add(q, A, x);
      mpz_mul(check, p, q);
      }
   std::cout << " p:       " << mpz_get_str (NULL, 10, p) << std::endl;
   std::cout << " q:       " << mpz_get_str (NULL, 10, q) << std::endl;
   std::cout << " smaller: " << mpz_get_str (NULL, 10, mpz_cmp(p, q) > 0 ? q : p) << std::endl;
   std::cout << std::endl << "Question3:" << std::endl;

   mpz_init (i1);
   mpz_init (i2);
   mpz_init (i1_squared);
   mpz_init (N_24);
   mpz_t six_N;
   mpz_set_str(N, "720062263747350425279564435525583738338084451473999841826653057981916355690188337790423408664187663938485175264994017897083524079135686877441155132015188279331812309091996246361896836573643119174094961348524639707885238799396839230364676670221627018353299443241192173812729276147530748597302192751375739387929", 10);
   std::cout << " N:       " << mpz_get_str (NULL, 10, N) << std::endl;
   mpz_init (six_N);
   mpz_mul_ui(six_N, N, 6); //mpz_mmod(six_N, six_N, N);
   
   // i1 = floor(sqrt(6N))
   mpz_sqrt(i1, six_N); //mpz_add_ui(i1, i1, 1);
   mpz_powm_ui(i1_squared, i1, 2, N); mpz_mmod(i1_squared, i1_squared, N); 
   mpz_set_str(check, "0", 10);
   
   // i2 = (sqrt(4(i1^2+i1-6N)+1))-1)/2
   mpz_add(i2, i1, i1_squared);
   mpz_sub(i2, i2, six_N); mpz_mmod(i2, i2, N); 
   mpz_mul_ui(i2, i2, 4);
   mpz_add_ui(i2, i2, 1); 
   mpz_sqrt(i2, i2);
   mpz_sub_ui(i2, i2, 1);
   mpz_cdiv_q_ui(i2, i2, 2);
  
   // i1 - i2 = 3p
   // i1 + i2 + 1 = 2q
   // (or the other way round)
   mpz_sub(p, i1, i2); int rem1 = mpz_cdiv_q_ui(p, p, 3);
   mpz_add(q, i1, i2); mpz_add_ui(q, q, 1); int rem2 = mpz_cdiv_q_ui(q, q, 2);
   if (rem1 != 0 || rem2 != 0)
   	  {
   	 	mpz_sub(p, i1, i2); mpz_cdiv_q_ui(p, p, 2);
   	 	mpz_add(q, i1, i2); mpz_add_ui(q, q, 1); mpz_cdiv_q_ui(q, q, 3);
    	}
   mpz_mul(check, p, q);
   std::cout << " p:       " << mpz_get_str (NULL, 10, p) << std::endl;
   std::cout << " q:       " << mpz_get_str (NULL, 10, q) << std::endl;
   mpz_mul(check, p, q);
   std::cout << " check:   " << mpz_get_str (NULL, 10, check) << std::endl;
   std::cout << " smaller: " << mpz_get_str (NULL, 10, mpz_cmp(p, q) > 0 ? q : p) << std::endl;
   return 0;
}
