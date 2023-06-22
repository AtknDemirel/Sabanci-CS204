//
//  SUBook.hpp
//  atakan.demirel_Demirel_Atakan_5
//
//  Created by Atakan Demirel on 10.12.2022.
//

#ifndef SUBook_h
#define SUBook_h

#include <string>
#include <vector>

using namespace std;

class Post;
class User;
class Comment;

class User
{
    friend class Post;
    friend class Comment;
    
private:
    string name;
    vector<Post*> post_vector;
    //ADDED
    //vector<Comment*> comment_vector;
    //ADDED OVER
    int num_comments;
    
public:
    User(string n);
    ~User();
    Post& createPost(string content);
    vector<Post*> getPosts();
    int getNumComments();
    string getName();
};

class Post
{
private:
    User & user;
    string content;
    vector <Comment*> comments;

public:
    Post(User & u, string s);
    ~Post();
    
    void addComment(string content, User* commenter);
    vector<Comment*> getComments();
    User& getUser();
    string getContent();
};

class Comment
{
private:
    User * user;
    string content;
    Post & post;

public:
    Comment(User * u, Post & p, string s);
    ~Comment();
    User& getUser();
    string getContent();
    Post& getPost();
};

#endif /* SUBook_h */
