//
//  SUBook.cpp
//  atakan.demirel_Demirel_Atakan_5
//
//  Created by Atakan Demirel on 10.12.2022.
//

#include "SUBook.h"


User::User(string n) : name(n) {
    num_comments = 0;
}

User::~User()
{
    for (int i = 0; i < post_vector.size(); i++)
    {
        delete post_vector[i];
    }
    //ADDED
    /*
    for (int i = 0; i < comment_vector.size(); i++)
    {
        delete comment_vector[i];
    }*/
    //ADDED OVER
}

Post& User::createPost(string content)
{
    Post *post = new Post(*this, content);
    post_vector.push_back(post);
    return *post;
}

int User::getNumComments()
{
    return num_comments;
}

string User::getName()
{
    return name;
}

vector<Post*> User::getPosts()
{
    return post_vector;
}

Post::Post(User & u, string s) : user(u), content(s) {}

Post::~Post()
{
    for (int i = 0; i < comments.size(); i++)
    {
        delete comments[i];
    }
}

User& Post::getUser()
{
    return user;
}

vector<Comment*> Post::getComments()
{
    return comments;
}

string Post::getContent()
{
    return content;
}

Comment::Comment(User * u, Post & p, string s) : user(u), post(p), content(s) {}

Comment::~Comment()
{
    this -> user -> num_comments--;
}

void Post::addComment(string content, User* commenter)
{
    Comment *comment = new Comment(commenter, *this, content);
    comments.push_back(comment);
    //ADDED
    //commenter -> comment_vector.push_back(comment);
    //ADDED OVER
    commenter -> num_comments++;
}

User& Comment::getUser()
{
    return *user;
}

string Comment::getContent()
{
    return content;
}

Post& Comment::getPost()
{
    return post;
}
