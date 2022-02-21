#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "tools.c"

void getCombinations(int nbr_combs, int length_comb, int combinaisons[nbr_combs][length_comb])
{
    // ABOUT THIS FUNCTION: get all possible combinations of (0, ..., 7)
    // INPUTS:
    //      nbr_combs: number of combinations (number of row for "combinations")
    //      length_comb: length of one combination (number of columns for "combinations")
    //      combinaisons: result array (all combinations)

    int comb[length_comb];
    memset(comb, 0, length_comb * sizeof(int));

    int one[length_comb];
    getOne(one, length_comb);

    combinaisons[0][0] = comb[0];
    combinaisons[0][1] = comb[1];
    combinaisons[0][2] = comb[2];
    combinaisons[0][3] = comb[3];

    for (int i = 1; i < nbr_combs; i++)
    {
        adder4(comb, one, comb);

        combinaisons[i][0] = comb[0];
        combinaisons[i][1] = comb[1];
        combinaisons[i][2] = comb[2];
        combinaisons[i][3] = comb[3];
    }
}

void getScore(int *comb1, int *comb2, int *score)
{
    // ABOUT THIS FUNCTION: get score of two combinations
    // INPUTS:
    //      comb1: first combination
    //      comb2: second combination
    //      score: resulting score (S1, S2)

    int S1 = 0;
    int S2 = 0;
    int elements_left1[4];
    int elements_left2[4];
    int index = 0;

    // numbers in the right position (S1)
    for (int i = 0; i < 4; i++)
    {
        if (comb1[i] == comb2[i])
        {
            S1++;
        }
        else
        {
            elements_left1[index] = comb1[i];
            elements_left2[index] = comb2[i];
            index++;
        }
    }

    // numbers in the wrong position (S2)
    for (int i = 0; i < index; i++)
    {
        for (int j = 0; j < index; j++)
        {
            if (elements_left1[i] == elements_left2[j])
            {
                S2++;
                break;
            }
        }
    }

    score[0] = S1;
    score[1] = S2;
}

void getResponses(int nbr_combs, int comb_length, int combinations[nbr_combs][comb_length], int nbr_responses, int response_length, int responses[nbr_responses][response_length])
{
    // ABOUT THIS FUNCTION: get all possible responses with their score
    // INPUTS:
    //      nbr_combs: number of combinations (number of row for "combinations")
    //      comb_length: length of one combination (number of columns for "combinations")
    //      combinaisons: result array (all combinations)

    //      nbr_responses: number of responses (number of row for "responses")
    //      response_length: length of one response (number of columns for "responses")
    //      responses: result array (all responses)

    // response example: {S1, S2, comb1, comb2}

    int score[2] = {0};
    int k = 0;

    for (int i = 0; i < nbr_combs; i++)
    {
        for (int j = i; j < nbr_combs; j++)
        {
            getScore(combinations[i], combinations[j], score);
            responses[k][0] = score[0];
            responses[k][1] = score[1];
            responses[k][2] = combinations[i][0];
            responses[k][3] = combinations[i][1];
            responses[k][4] = combinations[i][2];
            responses[k][5] = combinations[i][3];
            responses[k][6] = combinations[j][0];
            responses[k][7] = combinations[j][1];
            responses[k][8] = combinations[j][2];
            responses[k][9] = combinations[j][3];
            k++;
        }
    }
}

int getCombinaison(int comb_ref[], int score[], int nbr_responses, int response_length, int responses[nbr_responses][response_length], int *comb_res)
{
    // ABOUT THIS FUNCTION: get the corresponding reponses for a specific combination and score
    // INPUTS:
    //      comb_ref: combination reference
    //      score: score refetence
    //      combinaisons: result array (all combinations)

    //      nbr_responses: number of responses (number of row for "responses")
    //      response_length: length of one response (number of columns for "responses")
    //      responses: all responses

    //      comb_res: the resulting combination

    // OUTPUT:
    //      number of combinations * length of one combination

    int tmp_score[2] = {0, 0};
    tmp_score[0] = score[0];
    tmp_score[1] = score[1];

    int tmp_comb[4] = {0, 0, 0, 0};
    tmp_comb[0] = comb_ref[0];
    tmp_comb[1] = comb_ref[1];
    tmp_comb[2] = comb_ref[2];
    tmp_comb[3] = comb_ref[3];

    int index = 0;

    for (int i = 0; i < nbr_responses; i++)
    {
        if (responses[i][0] == tmp_score[0] &&
            responses[i][1] == tmp_score[1] &&
            responses[i][2] == tmp_comb[0] &&
            responses[i][3] == tmp_comb[1] &&
            responses[i][4] == tmp_comb[2] &&
            responses[i][5] == tmp_comb[3])
        {

            index = append(comb_res, index, responses[i][6]);
            index = append(comb_res, index, responses[i][7]);
            index = append(comb_res, index, responses[i][8]);
            index = append(comb_res, index, responses[i][9]);
        }
        else if (responses[i][0] == tmp_score[0] &&
                 responses[i][1] == tmp_score[1] &&
                 responses[i][6] == tmp_comb[0] &&
                 responses[i][7] == tmp_comb[1] &&
                 responses[i][8] == tmp_comb[2] &&
                 responses[i][9] == tmp_comb[3])
        {

            index = append(comb_res, index, responses[i][2]);
            index = append(comb_res, index, responses[i][3]);
            index = append(comb_res, index, responses[i][4]);
            index = append(comb_res, index, responses[i][5]);
        }
    }

    return index;
}

void pick_comb(int *arr, int arr_length, int *res)
{
    // ABOUT THIS FUNCTION: pick a combinaison randomly
    // INPUTS:
    //      arr: array of combinations
    //      arr_length: number of combinations * combination length
    //      res: picked combination

    srand(time(NULL));

    int nbr_combs = arr_length / 4;
    int random_index = (rand() % nbr_combs) * 4;

    res[0] = arr[random_index];
    res[1] = arr[random_index + 1];
    res[2] = arr[random_index + 2];
    res[3] = arr[random_index + 3];
}

int intersection(int *arr1, int *arr2, int length1, int length2, int *res)
{
    // ABOUT THIS FUNCTION: return the result of the intersection between two arrays (of combinations)
    // INPUTS:
    //      arr1: array of combinations
    //      arr2: array of combinations
    //      length1: (number of combinations * combination length) in the first array
    //      length2: (number of combinations * combination length) in the second array
    //      res: result of intersection
    // OUTPUT:
    //      number of combinations in the intersection list * combination length

    int index = 0;

    for (int i = 0; i < length1; i += 4)
    {
        for (int j = 0; j < length2; j += 4)
        {
            if (arr1[i] == arr2[j] &&
                arr1[i + 1] == arr2[j + 1] &&
                arr1[i + 2] == arr2[j + 2] &&
                arr1[i + 3] == arr2[j + 3])
            {
                index = append(res, index, arr1[i]);
                index = append(res, index, arr1[i + 1]);
                index = append(res, index, arr1[i + 2]);
                index = append(res, index, arr1[i + 3]);
            }
        }
    }

    return index;
}

void start_game(int nbr_responses, int response_length, int responses[nbr_responses][response_length])
{
    // initializations
    int step = 1;
    int score[2];
    int comb_ref[4] = {0, 0, 0, 0};
    int nbr_combs;
    int nbr_combs_tmp;
    int max_size = 50000; // TO DO : change the allocated memory

    int comb_res[max_size];
    memset(comb_res, 0, max_size * sizeof(int));

    int comb_res_tmp[max_size];
    memset(comb_res_tmp, 0, max_size * sizeof(int));

    // FIRST STEP
    printf("Proposition %d: \n", step);
    printf("%d %d %d %d\n", comb_ref[0], comb_ref[1], comb_ref[2], comb_ref[3]);

    printf("Combien de chiffre dans la bonne position: ");
    scanf("%d", &score[0]);

    printf("Combien de chiffre dans la mauvaise position: ");
    scanf("%d", &score[1]);

    printf("\n");

    nbr_combs = getCombinaison(comb_ref, score, nbr_responses, response_length, responses, comb_res);

    pick_comb(comb_res, nbr_combs, comb_ref);

    step++;

    // THE REST OF THE STEPS
    while (score[0] != 4)
    {
        printf("Proposition %d: \n", step);
        printf("%d %d %d %d\n", comb_ref[0], comb_ref[1], comb_ref[2], comb_ref[3]);

        printf("Combien de chiffre dans la bonne position: ");
        scanf("%d", &score[0]);

        printf("Combien de chiffre dans la mauvaise position: ");
        scanf("%d", &score[1]);

        printf("\n");

        nbr_combs_tmp = getCombinaison(comb_ref, score, nbr_responses, response_length, responses, comb_res_tmp);

        int res[max_size];
        memset(res, 0, max_size * sizeof(int));

        nbr_combs = intersection(comb_res, comb_res_tmp, nbr_combs, nbr_combs_tmp, res);
        copy(res, comb_res, nbr_combs);

        for (int i = 0; i < nbr_combs; i += 4)
        {
            printf("%d %d %d %d ", comb_res[i], comb_res[i + 1], comb_res[i + 2], comb_res[i + 3]);
            printf("\n");
        }

        pick_comb(comb_res, nbr_combs, comb_ref);

        step++;
    }
}

int main()
{
    // getting all possible combinations
    int base = 8;
    int nbr_bits = 4;
    int nbr_combs = pow(base, nbr_bits); // 4096 = 8^4
    int combinaisons[nbr_combs][nbr_bits];

    getCombinations(nbr_combs, nbr_bits, combinaisons);

    // getting all possible responses (with their combinations)
    int nbr_responses = 8390656; // C(n + r - 1, r) = (n + r - 1)! / r!(n - 1)!
    int response_length = 10;

    int(*responses)[response_length] = malloc(sizeof(int[nbr_responses][response_length]));
    getResponses(nbr_combs, nbr_bits, combinaisons, nbr_responses, response_length, responses);

    // START THE GAME
    start_game(nbr_responses, response_length, responses);
}