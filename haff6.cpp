#include <bits/stdc++.h>

typedef long long ll;

using namespace std;


struct Forest
{
    ll freq;
    int root;
    unsigned char symbol;
};

struct Tree
{
    int left = -1;
    int right = -1;
    int parent = -1;
    unsigned char symbol;
};

struct code{
    ll dl;
    int cod[256];
};

code coding[256];
Forest forest[256];
Tree tree[520];
FILE *f1, *f2, *f3;

void min_min(Forest forest[], int _size, ll &pos1, ll &pos2)
{
    if (forest[0].freq < forest[1].freq)
        pos1 = 0, pos2 = 1;
    else
        pos1 = 1, pos2 = 0;

    for (int i = 2; i < _size; i++)
    {
        if (forest[i].freq < forest[pos1].freq)
        {
            pos2 = pos1;
            pos1 = i;
        }
        else
            if (forest[i].freq < forest[pos2].freq)
        {
            pos2 = i;
        }
    }
}

int32_t main(int argc, char *argv[])
{
    /*argc = 3;
argv[1] = "encode";
argv[2] = "output.txt";
argv[3] = "input.txt";*/

    if (!strcmp("encode", argv[1]))
    {
    ll p1, p2;
    p1 = -1;
    p2 = -1;
    f1 = fopen(argv[3], "rb");
    f2 = fopen(argv[2], "wb");
    ll freq[256];
    memset(freq, 0, sizeof(freq));
    unsigned char ch = 0;
    while(fscanf(f1, "%c", &ch) != -1)
    {
        freq[ch]++;
    }
    int size_forest = 0;
    ll j = 0;
    for (int i = 0; i < 256; i++)
    {
        if (freq[i] != 0)
        {
            forest[j] = {freq[i], j, i};
            j++;
            size_forest++;
        }
    }

    for(int i = 0; i < j; i++)
    {
        tree[i].left = -1;
        tree[i].parent = -1;
        tree[i].right = -1;
        tree[i].symbol = forest[i].symbol;
    }
    int size_tree = size_forest;
    int size_num = size_forest;
    while (size_forest > 1)
    {
        min_min(forest, size_forest, p1, p2);


        tree[size_tree].left = forest[p1].root;
        tree[size_tree].right = forest[p2].root;
        tree[size_tree].parent = -1;

        tree[forest[p1].root].parent = size_tree;
        tree[forest[p2].root].parent = size_tree;

        forest[p1].freq += forest[p2].freq;
        forest[p1].root = size_tree;

        forest[p2] = forest[size_forest - 1];
        size_forest--;
        size_tree++;
    }

    for (int i = 0; i < size_num; i++)
    {
    ll element = i;
    ll par = tree[i].parent;
    ll sym = tree[i].symbol;
    coding[sym].dl = 0;
        while(par != -1)
        {
            if (tree[par].left == element )//== tree[tree[element].parent].left)
            {
                coding[sym].cod[coding[sym].dl] = 0;
            }
            else
                coding[sym].cod[coding[sym].dl] = 1;
            element = par;
            par = tree[par].parent;
            coding[sym].dl++;
        }
    }
    fseek(f1, 0, SEEK_SET);
    fprintf(f2, "\n%d\n", size_tree);
    for(int i = 0; i < size_tree; i++)
    {
        fprintf(f2, "%d %d %d %d\n", tree[i].left, tree[i].right, tree[i].parent, tree[i].symbol);
    }
    //cout << size_num << " ";

    //f1 = fopen("input.txt", "rb");
    unsigned char byte;
    byte = 0;
    ll dl_byte = 0;
    ll t = 0;
    while(fscanf(f1, "%c", &ch) != -1)
    {
        for (int i = coding[ch].dl - 1; i >= 0; i--)
        {
            if (dl_byte == 8)
            {
                fprintf(f2, "%c", byte);
                byte = 0;
                dl_byte = 0;
            }
            byte = byte * 2;
            byte += coding[ch].cod[i];
            dl_byte++;
        }
    }
if (byte > 0)
{
    for (int i = 0; i < 8 - dl_byte; i++)
    {
         byte = byte * 2;
    }
    fprintf(f2, "%c", byte);
}
fseek(f2, 0, SEEK_SET);
fprintf(f2, "%d", dl_byte);
fclose(f1);
fclose(f2);
}


else
{

    f1 = fopen(argv[2], "rb");
    f3 = fopen(argv[3], "wb");

    fseek(f1, 0, SEEK_END);
    fseek(f1, 0, SEEK_SET);

    ll size_tree, el, lst, dl_byt;
    lst = 0;
    unsigned char ch;
    fscanf(f1, "%d", &size_tree);
    el = size_tree - 1;

    for (int i = 0; i < size_tree; i++)
    {
        fscanf(f3, "%d%d%d%d ", &tree[i].left, &tree[i].right, &tree[i].parent, &tree[i].symbol);
        if (tree[i].left == -1)
        {
            lst++;
        }
    }
    while(fscanf(f1, "%c", &ch) != -1)
    {
        for (int i = 0; i < 8; i++)
        {
            if (el < lst)
            {
                fprintf(f3, "%c", tree[el].symbol);
                el = size_tree -1;
            }
            if ((int)ch / 128 == 0)
            {
                el = tree[el].left;
            }
            else
            {
                el = tree[el].right;
            }
            ch = ch * 2;
        }
    }
}
}
