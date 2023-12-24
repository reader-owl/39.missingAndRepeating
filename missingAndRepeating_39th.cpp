#include <iostream>

/*
                    Q. find the repeating and missing nmbr

                explanation -  we will be given an array of 'n' integers
                                arr[] = {4, 3, 6, 2, 1, 1}      n = 6
                                these integers are from 1 to 6 -  {1, 2, 3, 4, 5, 6}        <- these are from 1 to 6

                                if we compare both of them we get 4, 3, 6, 2, 1 from '1 to 6'
                                where 1 is repeated twice and 5 never appears in the array
                                        o/p we desired - {1, 5}

            Brute force -  by the given array we know that the elements are from 1 to 6
                            so we run a loop from 1 to 6
                            when iterating 1 through the loop we will get two 1's
                            we will get 2, 3, 4, 6
                            but 5 will be missing so it will appear 0 times

        pseudo code
repeating = -1, missing = -1
for(i=1->n)
{
    cnt = 0
    for(j=0->n-1)
    {
        if(arr[j] == i)
            cnt++;
    }
    if(cnt == 2)
        repeating = i;
    else if(cnt == 0)
        missing = i;
    if(repeating != -1 && missing != -1)
        break;
}

                TC - O(N^2)
                SC - O(1)


            Better sol  -  we will use hashing, we store elements in the hash map and keep track of how many times they appeared
                            all the nmbrs are from 1 to 6
                        we will declare a hash array = [0, 1, 2, 3, 4, 5, 6](<-indexes)    size of it will be 7
                        we initializes every element as '0'
                                            hash array = {0, 0, 0, 0, 0, 0, 0}
                                            indexes    =  0  1  2  3  4  5  6
                                which means none of the nmbr appears till now

                        then we will start iterating the arr[], on the '0'th index we got 4 so we increase the cnt of 4
                                i.e,        hash array = {0, 0, 0, 0, 1, 0, 0}

                        then next index we got 3, so        hash array = {0, 0, 0, 1, 1, 0, 0}
                        then next index we got 6, so        hash array = {0, 0, 0, 1, 1, 0, 1}
                        then next index we got 2, so        hash array = {0, 0, 1, 1, 1, 0, 1}
                        then next index we got 1, so        hash array = {0, 1, 1, 1, 1, 0, 1}
                        then next index we got 1, so        hash array = {0, 2, 1, 1, 1, 0, 1}

                        after iteration, we know that the elements are from 1 to 6 so we again start iterating from 1 to 6
                        start from 1 which has cnt of 2, so it will be our repeating nmbr
                        2 has cnt = 1
                        3 has cnt = 1
                        4 has cnt = 1
                        5 has cnt = 0, so it is our missing nmbr
                        6 has cnt = 1

        Actual code
vector<int> findMissingRepeatingNumbers(vector<int> a)
{
    int n = a.size();
    int hash[n+1] = {0};                    // size of hash array - [n+1], elements - {0}
    for(int i = 0; i < n; i++)              // O(n)
    {
        hash[a[i]]++;
    }
    
    int repeating = -1, missing = -1;
    for(int i = 1; i < n; i++)              // O(n)
    {
        if(hash[i] == 2)
            repeating = i;

        else if(hash[i] == 0)
            missing = i;

        if(repeating != -1 && misiing != -1)
        {
            break;
        }
    }
    return {repeating, missing};
}

        TC - O(2n)
        SC - O(n)               // bcz we are using extra hash array


            Optimal sol -  there are 2 optimal sol for this
                            1. maths
                            2. XOR

            1. optimal sol using math -  arr[] = {4, 3, 6, 2, 1, 1}     n = 6
                                        let's take  x -> repeating nmbr
                                                    y -> missing nmbr

                then sum up all the elements in the array
                                S = 4 + 3 + 6 + 2 + 1 + 1
                                S = 17

                lets sum up all the elements from 1 to 6
                               Sn = 1 + 2 + 3 + 4 + 5 + 6           // <- Sn = (n * (n+1)) / 2
                               Sn = 21

                then subsract Sn from S => S - Sn
                                        => {4 + 3 + 6 + 2 + 1 + 1} - {1 + 2 + 3 + 4 + 5 + 6}
                                        => (1 - 5)
                                        => -4

                    we also know that x is repeating nmbr and y is missing nmbr
                        so          x - y = -4          ..(1
                                and we never know if it is (1 - 5) or anything
                                from eq(1  we have to find another equation to get the velue of x and y
                       in order to do that, lets sum the square of each element
                                    S2 - S2n = {4^2 + 3^2 + 6^2 + 2^2 + 1^2 + 1^2} - {1^2 + 2^2 + 3^2 + 4^2 + 5^2 + 6^2}        // S2n = (n*(n+1)*(2n+1))/6
                                             = -24

                                    x^2 - y^2 = -24                // just like eq(1
                                (x - y)(x + y) = -24
                                (-4) * (x + y) = -24
                                        x + y  = 6          .. (2

                            from  (1  &  (2
                                x = 1,  y = 5

        Actual code
vector<int> findMissingRepeatingNumbers(vector<int> a)
{
    long long n = a.size();
    // S - Sn = x  y
    // S2 - S2N
    long long SN = (n * (n + 1)) / 2;
    long long S2N = (n * (n + 1) * (2*n + 1)) / 6;
    long long S = 0, S2 = 0;

    for(int i = 0; i < n; i++)
    {
        S += a[i];
        S2 += (long long)a[i] * (long long)a[i];            // these are int values, if we don't change them in 'long long' they might overflow
    }

    long long val1 = S - SN;        // x - y
    long long val2 = S2 - S2N;
    val2 = val2 / val1;             // x + y
    long long x = (val1 + val2) / 2;
    long long y = x - val1;
    return {(int)x, (int)y};
}

            TC - O(N)           // for using 1 loop
            SC - O(1)


            2. optimal sol using XOR method -  given array = {4, 3, 6, 2, 1, 1}     n = 6
                                                again  x -> repeating
                                                       y -> missing

                                            let's XOR all the elements of the array, along with first n natural nmbrs and XOR them too

                                                            => (4^3^6^2^1^1)^(1^2^3^4^5^6)
                                                            => (1^5)                            // 001 ^ 101 = 100
                                                            =>  4

                                                we also know that, x is repeating as '1' and y is missing as '5'
                                                so    x ^ y => 4

                                                watch video for explanation

        Actual code
vector<int> findMissingRepeatingNumbers(vector<int> a)
{
    long long n = a.size();
    int xr = 0;
    for(int i = 0; i < n; i++)
    {
        xr = xr ^ a[i];
        xr = xr ^ (i + 1);
    }
    int bitNo = 0;
    while(1)
    {
        if(xt & (1 << bitNo) != 0)
            break;

        bitNo++;
    }
    int zero = 0
    int one = 0;
    for(int i = 0; i < n; i++)
    {
        // part of 1 club
        if((a[i] & (1<< bitNo)) != 0)
        {
            one = one ^ a[i];
        }
        // zeroth club
        else
        {
            zero = zero ^ a[i];
        }
    }

    for(int i = 1; i <= n; i++)
    {
        // part of 1 club
        if((i & (1 << bitNo)) != 0)
        {
            one = one ^ 1;
        }
        // zeroth club
        else
        {
            zero = zero ^ 1;
        }
    }

    int cnt = 0;
    for(int i = 0; i < n; i++)
    {
        if(a[i] == zero)
            cnt++;
    }

    if(cnt == 2)
        return {zero, one};

    return {zero, one};
}

            TC - O(N)
            SC - O(1)
*/

int main()
{
    std::cout << "Hello World!\n";
}