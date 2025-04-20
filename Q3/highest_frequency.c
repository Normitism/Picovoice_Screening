    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    // Create hashmap implementation for efficient tracking of frequencies
    #define TABLE_SIZE 405521

    // create bucket struct
    typedef struct Entry{
        char* key;
        int val;
        struct Entry* next; //deal with collisions
    }Entry;

    // create the table that also holds the highest frequent word
    typedef struct{
        char* f_word;
        int freq;
        Entry* buckets[TABLE_SIZE];
    }Hashmap;

    //hashkey generator using 
    unsigned long hash(const char* key){
        unsigned long hash = 5381;
        int c;
        while ((c = *key++)){
            hash = ((hash << 5) + hash) + c;
        }
        return hash % TABLE_SIZE;
    }

    //insert/update func
    void insert(Hashmap* map, const char* key, int val){
        unsigned long index = hash(key);
        //get current bucket
        Entry* current = map->buckets[index];
        //search for value within bucket
        while (current){
            if (strcmp(current->key, key) == 0){
                current->val = val;
                return;
            }
            current = current->next;
        }
        //if it is not pre existing create new entry and add it to the head of bucket
        Entry* newEntry = malloc(sizeof(Entry));
        newEntry->key = strdup(key);
        newEntry->val = val;
        newEntry->next = map->buckets[index];
        map->buckets[index] = newEntry;
    }

    //get func
    int get(Hashmap* map, const char* key){
        unsigned long index = hash(key);
        //get current bucket
        Entry* current = map->buckets[index];
        while (current){
            if (strcmp(current->key, key) == 0){
                return current->val;
            }
            current = current->next;
        }
        return 0;
    }

    //deallocation func
    void free_Hashmap(Hashmap* map){
        for (int i = 0; i<TABLE_SIZE; i++){
            Entry* current = map->buckets[i];
            while (current){
                Entry* next = current->next;
                free(current->key);
                free(current);
                current = next;
            }
        }
    }
    void remove_char(char* line, int i) {
        while (line[i] != '\0') {
            line[i] = line[i + 1]; 
            i++;
        }
    }
    void normallize_line(char* line, char*** buffer, int max_words, int max_word_len){
        //allocate memory for the buffer and init
        *buffer = malloc(max_words*sizeof(char*));
        for(int i = 0; i < max_words; i++){
            (*buffer)[i] = malloc(max_word_len*sizeof(char));
            memset((*buffer)[i], 0, max_word_len);
        }
        int word_ind = 0;
        int letter_ind = 0;

        for (int i = 0; line[i] != '\0'; i++){
            if (isalpha(line[i])){
                (*buffer)[word_ind][letter_ind++] = tolower(line[i]);
            }else if(line[i] == '\''){
                (*buffer)[word_ind][letter_ind++] = '\'';
            }else{
                if (letter_ind > 0){
                    (*buffer)[word_ind][letter_ind] = '\0';
                    word_ind++;
                    letter_ind = 0;
                }

                while(!isalpha(line[i]) && line[i] != '\'' && line[i] != '\0'){
                    i++;
                }
                i--;
            }

        }
        if (letter_ind > 0){
            (*buffer)[word_ind][letter_ind] = '\0';
        }

    }

    //takes each line and enters it into the hashmap
    void word_counter(Hashmap* map, char* line){
        // initialize a storage buffer
        int max_words = 20;
        int max_word_len = 20;
        char** buffer;
        printf("%s \n", line);
        // normallize each line and divide it into an array of words
        normallize_line(line, &buffer, max_words, max_word_len);
        for (int i =0; i < i < max_words&& buffer[i][0] != '\0'; i++){
            printf("%s ",buffer[i]);
        }
        printf("\n");
        for(int i = 0; i < max_words && buffer[i][0] != '\0'; i++){
            
            int curr_count = get(map, buffer[i]);
            curr_count++;
            insert(map, buffer[i], curr_count);
            if (curr_count > map->freq){
                if (map->f_word){
                    free(map->f_word);
                }
                map->f_word = strdup(buffer[i]);
                map->freq = curr_count;
            }


        }
        for (int i = 0; i < max_words; i++){
            free(buffer[i]);
        }
        free(buffer);    


    }
    // open and read the file then count the frequencies of characters
    void read_shakespeare(const char* filename, Hashmap* map){
        FILE* file = fopen(filename, "r");
        if(!file) {
            perror("Error opening file");
            return;
        }
        //line buffer
        char line[200];
        while (fgets(line, sizeof(line), file)){
            // replace \n with \0 so normallize line functions as intended
            line[strcspn(line,"\n")] = '\0';
            word_counter(map, line);
        }if (ferror(file)) {
            perror("Error reading file");
        }
        fclose(file);

    }
    int main() {
        // init
        // heap allocate so it doesnt blow up the stack 
        Hashmap* map = malloc(sizeof(Hashmap));
        memset(map, 0, sizeof(Hashmap));
        map->f_word = NULL;
        map->freq = 0;
        //open file and read and record
        const char* filename = "shakespeare.txt";
        read_shakespeare(filename, map);
        int thy_f = get(map, "shall");
        printf("%d\n", thy_f);
        printf("most frequent word: %s\n", map->f_word);
        printf("'%s' appeared %d times\n",map->f_word, map->freq);

        free_Hashmap(map);
        free(map);
        return 0;
        
    }