#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <string>
#include <fstream>

char* filename = INPUTDIR "../app/input.txt";

extern "C"{
#include "text.h"
#include "_text.h"
#include "common.h"
}

TEST(load, num1){
    text txt = create_text();
    load(txt, filename);
    std::ifstream f;
    f.open(filename);
    std::string s;
    node *current = txt->begin;
    EXPECT_NE(txt->begin, nullptr);
    EXPECT_NE(txt->end, nullptr);
    while (std::getline(f, s)){
        EXPECT_EQ(current->contents, s);
        current = current->next;
    }
}


TEST(load, num2){
    text txt = create_text();
    testing::internal::CaptureStdout();
    load(txt, "exist.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "The file exist.txt cannot be opened\n");
}


TEST(move, num1){
    text txt = create_text();
    load(txt, filename);
    move(txt, 3, 3);
    EXPECT_EQ(txt->cursor->position, 3);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line){
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, 3);
    remove_all(txt);
}


TEST(move, num2){
    text txt = create_text();
    load(txt, filename);
    move(txt, -5, 0);
    EXPECT_EQ(txt->cursor->position, 0);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line){
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, 1);
    remove_all(txt);
}


TEST(move, num3){
    text txt = create_text();
    load(txt, filename);
    move(txt, 100, 0);
    EXPECT_EQ(txt->cursor->position, 0);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line){
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, txt->length);
    remove_all(txt);
}


TEST(move, num4){
    text txt = create_text();
    load(txt, filename);
    move(txt, 2, -2);
    EXPECT_EQ(txt->cursor->position, 0);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line){
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, 2);
    remove_all(txt);
}


TEST(move, num5){
    text txt = create_text();
    load(txt, filename);
    move(txt, 2, 100);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line){
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, 2);
    EXPECT_EQ(txt->cursor->position, strlen(txt->cursor->line->contents));
    remove_all(txt);
}


TEST(move, num6){
    text txt = create_text();
    testing::internal::CaptureStderr();
    move(txt, 1, 1);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "There are already no any lines in the text!\n");
    remove_all(txt);
}


TEST (save, num1){
    text txt = create_text();
    testing::internal::CaptureStderr();
    save(txt, "save.txt");
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "There are already no any lines in the text!\n");
    remove_all(txt);
}


TEST(save, num2){
    text txt = create_text();
    load(txt, filename);
    save(txt, "save.txt");
    std::ifstream f;
    f.open(filename);
    std::ifstream cur_f;
    cur_f.open("save.txt");
    std::string s;
    std::string cur_s;
    while(std::getline(f, s) && std::getline(cur_f, cur_s)){
        EXPECT_EQ(s, cur_s);
    }
    EXPECT_FALSE(std::getline(f, s) || std::getline(cur_f, cur_s));
    f.close();
    cur_f.close();
    remove_all(txt);
}


TEST(show, num1){
    text txt = create_text();
    load(txt, filename);
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();
    int i = 0;
    node *current = txt->begin;
    while(current){
        for (int j = 0; j < strlen(current->contents); j++){
            EXPECT_EQ(output[i], current->contents[j]);
            i++;
        }
        if (current != txt->end)
            i++;
        current = current->next;
    }
    EXPECT_EQ(output[i], '|');
    remove_all(txt);
}


TEST(show, num2){
    text txt = create_text();
    load(txt, filename);
    move(txt, 3, 2);
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();
    int i = 0;
    node *current = txt->begin;
    while(current){
        for (int j = 0; j < strlen(current->contents); j++){
            if (current == txt->cursor->line
                   && j == txt->cursor->position){
                EXPECT_EQ(output[i], '|');
                i++;
            }

            EXPECT_EQ(output[i], current->contents[j]);
            i++;
        }
        i++;
        current = current->next;
    }
    remove_all(txt);
}


TEST(show, num3){
    text txt = create_text();
    testing::internal::CaptureStderr();
    show(txt);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "There are already no any lines in the text!\n");

    remove_all(txt);
}


TEST(showupfirst, num1){
    text txt = create_text();
    load(txt, filename);
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();
    int i = 0;
    node *current = txt->begin;
    while(current){
        for (int j = 0; j < strlen(current->contents); j++){
            if (j > 0 && current->contents[j - 1] == ' ' &&
                    current->contents[j] >= 'a' && current->contents[j] <= 'z'){
                EXPECT_EQ(output[i], current->contents[j] - 'a' + 'A');
            }else{
                EXPECT_EQ(output[i], current->contents[j]);
            }
            i++;
        }
        if (current != txt->end)
            i++;
        current = current->next;
    }
    EXPECT_EQ(output[i], '|');
    remove_all(txt);
}


TEST(showupfirst, num2){
    text txt = create_text();
    testing::internal::CaptureStderr();
    showupfirst(txt);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "There are already no any lines in the text!\n");

    remove_all(txt);
}


TEST(mle, num1){
    text txt = create_text();
    load(txt, filename);
    move(txt, 3, 2);
    mle(txt);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line){
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, 3);
    EXPECT_EQ(txt->cursor->position, strlen(txt->cursor->line->contents));
    remove_all(txt);
}


TEST(mle, num2){
    text txt = create_text();
    load(txt, filename);
    txt->cursor->line = NULL;
    txt->cursor->position = 0;
    testing::internal::CaptureStderr();
    mle(txt);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "No cursor!\n");
    remove_all(txt);
}


TEST(r1ne, num1){
    text txt = create_text();
    load(txt, filename);
    r1ne(txt);
    std::ifstream f;
    f.open(filename);
    std::string s;
    node *current = txt->begin;
    EXPECT_NE(txt->begin, nullptr);
    EXPECT_NE(txt->end, nullptr);
    std::getline(f, s);
    while (std::getline(f, s)){
        EXPECT_EQ(current->contents, s);
        current = current->next;
    }
}


TEST(r1ne, num2){
    text txt = create_text();
    load(txt, filename);
    r1ne(txt);
    r1ne(txt);
    std::ifstream f;
    f.open(filename);
    std::string s;
    node *current = txt->begin;
    EXPECT_NE(txt->begin, nullptr);
    EXPECT_NE(txt->end, nullptr);
    std::getline(f, s);

    std::getline(f, s);
    EXPECT_EQ(current->contents, s);
    current = current->next;

    std::getline(f, s);
    while (std::getline(f, s)){
        EXPECT_EQ(current->contents, s);
        current = current->next;
    }
}


TEST(r1ne, num3){
    text txt = create_text();
    load(txt, filename);
    EXPECT_NE(txt->begin, nullptr);
    EXPECT_NE(txt->end, nullptr);
    for (int i = 0; i < 10; i++){
        r1ne(txt);
    }

    testing::internal::CaptureStderr();
    r1ne(txt);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ("The text is not empty lines\n", output);
}
