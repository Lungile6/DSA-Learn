#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256
#define MAX_TREE_HT 100

// Huffman Tree node
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// MinHeap (priority queue)
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// ===================== Utility Functions =====================

struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[--minHeap->size];
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* node) {
    int i = minHeap->size++;
    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--)
        minHeapify(minHeap, i);
}

int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// ===================== Tree Building =====================

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// ===================== Code Generation =====================

char codes[SIZE][MAX_TREE_HT];

void storeCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root)) {
        for (int i = 0; i < top; i++)
            codes[(unsigned char)root->data][i] = arr[i] + '0';
        codes[(unsigned char)root->data][top] = '\0';
    }
}

// ===================== Encoding =====================

void encodeText(const char* text, char* encodedStr) {
    encodedStr[0] = '\0';
    for (int i = 0; text[i] != '\0'; i++) {
        strcat(encodedStr, codes[(unsigned char)text[i]]);
    }
}

// ===================== Decoding =====================

void decodeText(struct MinHeapNode* root, const char* encodedStr) {
    struct MinHeapNode* curr = root;
    printf("\nDecoded Output:\n");
    for (int i = 0; encodedStr[i] != '\0'; i++) {
        if (encodedStr[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;
        if (isLeaf(curr)) {
            printf("%c", curr->data);
            curr = root;
        }
    }
    printf("\n");
}

// ===================== Main =====================

int main() {
    char input[1000];
    printf("Enter text to encode: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    // Step 1: Count frequencies
    int freq[SIZE] = {0};
    for (int i = 0; input[i]; i++)
        freq[(unsigned char)input[i]]++;

    char chars[SIZE];
    int charFreq[SIZE], size = 0;

    for (int i = 0; i < SIZE; i++) {
        if (freq[i]) {
            chars[size] = (char)i;
            charFreq[size++] = freq[i];
        }
    }

    // Step 2: Build Huffman Tree
    struct MinHeapNode* root = buildHuffmanTree(chars, charFreq, size);

    // Step 3: Generate Huffman Codes
    int arr[MAX_TREE_HT];
    storeCodes(root, arr, 0);

    // Step 4: Encode Text
    char encoded[10000];
    encodeText(input, encoded);
    printf("\nEncoded Output:\n%s\n", encoded);

    // Step 5: Decode Text
    decodeText(root, encoded);

    return 0;
}
