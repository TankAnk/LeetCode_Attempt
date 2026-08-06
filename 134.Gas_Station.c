/*
  - If [start, end] fails, jump to end + 1, reset current gas to 0 and assume new valid start is end + 1
  - Keep track of total gas overall to validate start
*/

int canCompleteCircuit(int *gas, int gasSize, int *cost, int costSize)
{
  int curr_gas = 0, start = 0, total = 0;
  for (int i = 0; i < gasSize; i++)
  {
    int diff = gas[i] - cost[i];
    curr_gas += diff;
    total += diff;

    if (curr_gas < 0)
    {
      start = i + 1;
      curr_gas = 0;
    }
  }

  return (total < 0 ? -1 : start);
}

/*
 gas 01 02 03 04 05
 cos 03 04 05 01 02
 dif -2 -2 -2 03 03

 gas 02 03 04
 cos 03 04 03
 dif -1 -1 01
 */
