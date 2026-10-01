/* Sieve of Eratosthenes
   let A be an array of Boolean values, indexed by integers 2 to n, initially all set to true.
   for i = 2, 3, 4, ..., not exceeding sqrt(n) do
     if A[i] is true
       for j = i^2, i^2+i, i^2+2i, i^2+3i, ..., not exceeding n do
         set A[j] to false

   return all i such that A[i] is true.
*/

int countPrimes(int n)
{
  if (n <= 2)
    return 0;

  /*
   * Initially, treat every number from 2 through n - 1 as acandidate prime
   * Since 0 and 1 are known not to be prime, there are initially n - 2 possible prime numbers
   * We will decrease this count whenever we discover that a number is definitely composite
   */
  int result = n - 2;

  /*
   * is_prime[x] represents whether x is still considered to be a possible prime number
   *     is_prime[x] == true -> x has not been proven to be composite yet
   *     is_prime[x] == false -> x has been proven to be composite
   */
  bool is_prime[n];

  /*
   * Initially, none of the numbers have been identified as composite, mark every element as true
   */
  memset(is_prime, 1, n * sizeof(*is_prime));

  /*
   * For each possible prime i, we mark every multiple of i as composite
   * Only need to check values of i up to sqrt(n) because every composite number must have at least 1 factor <= its square root
   */
  for (int i = 2; i <= n / i; i++)
  {
    /*
     * If i has already been marked as composite, there is no need to process its multiples
     * For example: if i = 6, we already know that 6 is composite because it was previously marked by 2 or 3
     * Every multiple of 6 is also a multiple of either 2 or 3, so those multiples have already been handled
     */
    if (!is_prime[i])
      continue;

    /*
     * Start marking multiples from i * i instead of 2 * i
     * Every multiple of i that is smaller than i * i has already been marked by a smaller factor.
     * For example, when i = 5:
     *     2 * 5 = 10  -> already marked when processing 2
     *     3 * 5 = 15  -> already marked when processing 3
     *     4 * 5 = 20  -> already marked when processing 2
     * Therefore, the first multiple that can be newly discovered using i is i * i:
     *     5 * 5 = 25
     *
     * After that, adding i repeatedly gives every subsequent multiple of i
     */
    for (int j = i * i; j < n; j += i)
    {
      /*
       * Check whether j has already been marked as composite
       *
       * A number can have more than one prime factor. For example: 30 is divisible by 2, 3, 5
       * When processing 2, we mark 30 as composite and decrease result once.
       * Later, when processing 3 or 5, 30 is already marked false,so we do not decrease again
       * This guarantees that every composite number is removed from the prime count exactly once
       */
      if (is_prime[j])
      {
        /*
         * j is divisible by i, so j is definitely composite
         * Remove it from the number of possible primes
         */
        result--;

        /*
         * Remember that j has already been identified as composite
         */
        is_prime[j] = false;
      }
    }
  }

  return result;
}
