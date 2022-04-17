#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <set>
#include <queue>
#include "BST.h"

using namespace std;

// forward declarations for Actor & Director
class Director;
class Actor;
class MovieNode;
class Movie;

template <class A>
class Node
{
public:
    A _value;

    Node *_next = NULL;
};

// stores 3 attributes of a director
class Director
{
public:
    // attributes' variables declared
    string _name;
    string _fBLikes;
    Node<Movie *> *_movies = new Node<Movie *>();
};

// stores 3 attributes of a actor
class Actor
{
public:
    // attributes' variables declared
    string _name;
    string _fBLikes;
    Node<Movie *> *_movies = new Node<Movie *>();
};

// stores 28 attributes of a movie
class Movie
{
public:
    // attributes' variables declared
    Node<string> *_genres = new Node<string>(), *_plotKeywords = new Node<string>();
    string _name, _imdbLink, _language, _country, _contentRating, _color;
    Director *_director = new Director();
    Actor *_actor1 = new Actor(), *_actor2 = new Actor(), *_actor3 = new Actor();
    string _gross, _numOfVoters, _totalCast, _budget, _fBLikes;
    string _releaseYear, _duration, _facesInPoster, _usersForReviews, _numOfCritics;
    string _imdbScore, _aspectRatio;
};

// Node to store a movie
class MovieNode
{
public:
    // member variables for a node of Movie in collection
    Movie *_value = new Movie();
    int _balanceFactor;
    MovieNode *_left = NULL;
    MovieNode *_right = NULL;

    // no-arg constructor
    MovieNode()
    {
        _balanceFactor = 0;
    }

    // parameterized constructor
    MovieNode(Movie *movie)
    {
        _value = movie;
        _balanceFactor = 0;
    }
};

// Node to store an Actor
class ActorNode
{
public:
    // member variables for a node of Actor in collection
    Actor *_value = new Actor();
    int _balanceFactor = 0;
    ActorNode *_left = NULL;
    ActorNode *_right = NULL;

    // parameterized constructor
    ActorNode(Actor *actor)
    {
        _value = actor;
    }
};

// Node to store a director
class DirectorNode
{
public:
    // member variables for a node of Director in collection
    Director *_value = new Director();
    int _balanceFactor = 0;
    DirectorNode *_left = NULL;
    DirectorNode *_right = NULL;

    // parameterized constructor
    DirectorNode(Director *director)
    {
        _value = director;
    }
};

// tokenizes the given string on the del arg
vector<string> tokenize(string s, string del = ",")
{
    // start & end points
    int start = 0;
    int end = s.find(del);

    // vector of individual cells
    vector<string> cells;
    string name;

    // -1 means not found
    while (end != -1)
    {

        // using sub string method
        cells.push_back(s.substr(start, end - start));

        // updating start & end values
        start = end + del.size();
        end = s.find(del, start);
    }

    // last cell
    cells.push_back(s.substr(start, end - start));

    if (cells.size() > 28)
    {
        for (int i = 0; i < (cells.size() - 28); i++)
        {
            cells.at(0) += ("," + cells.at(i + 1));
        }
    }

    return cells;
}


/*
    Reads the data from given csv file
    Makes a node for each movie, actor & director
    Inserts it into the corresponding hashmap
*/
class MovieCollection
{
public:
    // map for storing movies sorted name wise
    map<char, BST<MovieNode, Movie> *> _mapMovieNames;

    // map for storing movies sorted genre wise
    map<string, BST<MovieNode, Movie> *> _mapMovieGenre;

    // map for storing movies sorted release year wise
    map<string, BST<MovieNode, Movie> *> _mapMovieYear;

    // map for storing actors sorted name wise
    map<char, BST<ActorNode, Actor> *> _mapActorNames;

    // map for storing directors sorted name wise
    map<char, BST<DirectorNode, Director> *> _mapDirectorNames;

    // BST for storing the movies rating wise
    BST<MovieNode, Movie> *_BSTMovieRating = new BST<MovieNode, Movie>();

    void moviesRatingWise()
    {
        // calling the descending order print function of our AVL
        _BSTMovieRating->DescendingOrder(_BSTMovieRating->_root);
    }

    // takes an actor's name, FB likes & movies
    // returns an Actor ptr
    Actor *ptrActor(string name, string fBLikes, Movie *movie)
    {
        // creating an Actor object
        Actor *actor = new Actor();

        // assigning values
        actor->_name = name;
        actor->_fBLikes = fBLikes;
        actor->_movies->_value = movie;

        return actor;
    }

    Director *ptrDirector(string name, string fBLikes, Movie *movie)
    {
        // creating a Director Object
        Director *director = new Director();

        // assigning values
        director->_name = name;
        director->_fBLikes = fBLikes;
        director->_movies->_value = movie;

        return director;
    }

    // takes a vector of attributes of a movie
    // returns a Movie ptr
    Movie *ptrMovie(vector<string> atts)
    {
        // creating the movie object
        Movie *mov = new Movie();

        // assigning values
        mov->_name = atts.at(0);
        mov->_releaseYear = atts.at(2);
        mov->_imdbScore = atts.at(3);
        mov->_numOfCritics = atts.at(6);
        mov->_duration = atts.at(7);
        mov->_gross = atts.at(14);
        mov->_numOfVoters = atts.at(15);
        mov->_totalCast = atts.at(16);
        mov->_facesInPoster = atts.at(17);
        mov->_imdbLink = atts.at(19);
        mov->_usersForReviews = atts.at(20);
        mov->_language = atts.at(21);
        mov->_country = atts.at(22);
        mov->_contentRating = atts.at(23);
        mov->_budget = atts.at(24);
        mov->_aspectRatio = atts.at(25);
        mov->_fBLikes = atts.at(26);
        mov->_color = atts.at(27);

        // assigning genres
        vector<string> multiValues = tokenize(atts.at(1), "|");

        // placing genres
        Node<string> *temp1 = mov->_genres;
        for (auto genre = multiValues.begin(); genre != multiValues.end(); ++genre)
        {
            temp1->_value = *genre;
            temp1->_next = new Node<string>();
            temp1 = temp1->_next;
        }

        // assigning plot keywords
        multiValues = tokenize(atts.at(18), "|");

        // placing plot keywords
        Node<string> *temp2 = mov->_plotKeywords;
        for (auto plotKeyWord = multiValues.begin(); plotKeyWord != multiValues.end(); ++plotKeyWord)
        {
            temp2->_value = *plotKeyWord;
            temp2->_next = new Node<string>();
            temp2 = temp2->_next;
        }

        // vector to store actor1, actor2, actor3 pointers
        vector<Actor *> actors;

        for (int i = 8; i < 13; i = i + 2)
        {
            // key from the name of the actor
            char key = (char)tolower(atts.at(i)[0]);

            Actor *actor;

            // if key i.e. first letter of actor name, doesn't exist in map
            if (_mapActorNames.count(key) != 1)
            {
                // placing an AVL Tree there
                _mapActorNames[key] = new BST<ActorNode, Actor>();

                // saving for later use
                actor = ptrActor(atts.at(i), atts.at(i + 1), mov);

                // inserting actor in AVL
                _mapActorNames[key]->insertNode(actor);
            }

            else
            {
                // search result saved
                ActorNode *found = _mapActorNames[key]->Search(atts.at(i));

                // search if actor's already in AVL
                if (found == NULL)
                {
                    // saving for later use
                    actor = ptrActor(atts.at(i), atts.at(i + 1), mov);

                    // inserting actor in AVL
                    _mapActorNames[key]->insertNode(actor);
                }

                else
                {
                    // new node for movies' linked list
                    Node<Movie *> *movie = new Node<Movie *>();
                    movie->_value = mov;

                    // inserting movie at head
                    movie->_next = found->_value->_movies->_next;
                    found->_value->_movies->_next = movie;

                    // saving for later use
                    actor = found->_value;
                }
            }

            // placing actor in the vector
            actors.push_back(actor);
        }

        // placing the actors
        mov->_actor1 = actors.at(0);
        mov->_actor2 = actors.at(1);
        mov->_actor3 = actors.at(2);

        // first letter of director as key
        char key = (char)tolower(atts.at(4)[0]);

        Director *director;

        if (_mapDirectorNames.count(key) != 1)
        {
            // placing an AVL Tree
            _mapDirectorNames[key] = new BST<DirectorNode, Director>();

            // saving for later use
            director = ptrDirector(atts.at(4), atts.at(5), mov);

            // inserting director in AVL
            _mapDirectorNames[key]->insertNode(director);
        }

        else
        {
            // search result saved
            DirectorNode *found = _mapDirectorNames[key]->Search(atts.at(4));

            // checking if director's already in AVL
            if (found == NULL)
            {
                // saving for later use
                director = ptrDirector(atts.at(4), atts.at(5), mov);

                // inserting director in AVL
                _mapDirectorNames[key]->insertNode(director);
            }

            else
            {
                // new node for movies' linked list
                Node<Movie *> *movie = new Node<Movie *>();
                movie->_value = mov;

                // inserting movie at head
                movie->_next = found->_value->_movies->_next;
                found->_value->_movies->_next = movie;

                // saving for later use
                director = found->_value;
            }
        }

        // placing director
        mov->_director = director;

        return mov;
    }

    // reads a csv....
    void dataReader()
    {
        // file stream
        fstream movieData("IMDB_Top5000-SEECS.csv");

        string record;
        vector<string> cells;

        // header line
        getline(movieData, record);

        // reading line by line
        while (!movieData.eof())
        {
            getline(movieData, record);

            // vector of cells
            cells = tokenize(record);

            // key for the hashmap (name wise)
            char keyName = (char)tolower(record[0]);

            Movie *currentMovie = ptrMovie(cells);

            // populating AVL of movies rating wise
            _BSTMovieRating->insertInAVLRatingWise(currentMovie);

            // inserting in hashmap (name wise)
            if (_mapMovieNames.count(keyName) != 1)
                _mapMovieNames[keyName] = new BST<MovieNode, Movie>();

            _mapMovieNames[keyName]->insertNode(currentMovie);

            // inserting in hashmap (genre wise)
            vector<string> genres = tokenize(cells.at(1), "|");

            for (auto i = genres.begin(); i != genres.end(); ++i)
            {
                // key for each genre in the map
                string keyGenre = *i;

                if (_mapMovieGenre.count(keyGenre) != 1)
                    _mapMovieGenre[keyGenre] = new BST<MovieNode, Movie>();

                _mapMovieGenre[keyGenre]->insertNodeRatingWise(currentMovie);
            }

            // inserting in hashmap (year wise)
            string keyYear = cells.at(2);

            if (_mapMovieYear.count(keyYear) != 1)
                _mapMovieYear[keyYear] = new BST<MovieNode, Movie>();

            _mapMovieYear[keyYear]->insertNodeYearWise(currentMovie);

           
        }

        
    }

    set<Actor *> searchCoActor(string actor1_name, string actor2_name = "")
    {
        set<Actor *> actors;
        map<Actor *, Node<Movie *>> coActors;
        char key1 = (char)tolower(actor1_name[0]);
        ActorNode *actorNode = _mapActorNames[key1]->Search(actor1_name);
        if (actorNode == NULL)
        {
            cout << "Actor not found" << endl;
            return actors;
        }
        Actor *original_Actor = actorNode->_value;

        Node<Movie *> *actorMovies = original_Actor->_movies;
        Movie *movie1;
        while (actorMovies != NULL)
        {
            movie1 = actorMovies->_value;
            if (actor2_name != "noactor")
                cout << "Movie Name: " << movie1->_name;
            if (movie1->_actor1 != NULL && movie1->_actor1 != original_Actor && movie1->_actor1->_name != actor2_name)
            {
                actors.insert(movie1->_actor1);
                if (actor2_name != "noactor")
                    cout << "  Actor: " << movie1->_actor1->_name;
            }

            if (movie1->_actor2 != NULL && movie1->_actor2 != original_Actor && movie1->_actor2->_name != actor2_name)
            {
                actors.insert(movie1->_actor2);
                if (actor2_name != "noactor")
                    cout << "  Actor: " << movie1->_actor2->_name;
            }

            if (movie1->_actor3 != NULL && movie1->_actor3 != original_Actor && movie1->_actor3->_name != actor2_name)
            {
                actors.insert(movie1->_actor3);
                if (actor2_name != "noactor")
                    cout << "  Actor: " << movie1->_actor3->_name;
            }

            if (actor2_name != "noactor")
                cout << endl;
            actorMovies = actorMovies->_next;
        }
        return actors;
    }

    void coActorOfcoActor(string actor1_name)
    {
        set<Actor *> coActors = searchCoActor(actor1_name, "noactor");
        set<Actor *>::iterator itr;
        set<Actor *>::iterator itr2;
        set<Actor *> coActorsOfcoActors;
        set<Actor *> temp;
        cout << "\nThe coActors of coActors of " << actor1_name << " are: " << endl;
        for (itr = coActors.begin(); itr != coActors.end(); itr++)
        {
            temp = searchCoActor((*itr)->_name, "noactor");
            for (itr2 = temp.begin(); itr2 != temp.end(); itr2++)
            {
                // cout << *itr2 << endl;
                if ((*itr2)->_name != actor1_name)
                    coActorsOfcoActors.insert((*itr2));
            }
        }
        for (itr2 = coActorsOfcoActors.begin(); itr2 != coActorsOfcoActors.end(); itr2++)
        {
            auto pos = coActors.find((*itr2));
            if (pos == coActors.end())
                cout << (*itr2)->_name << endl;
        }
    }

    void coActorTest(string actor1_name, string actor2_name)
    {
        char key1 = (char)tolower(actor1_name[0]);
        char key2 = (char)tolower(actor2_name[0]);
        Actor *actor1 = _mapActorNames[key1]->Search(actor1_name)->_value;
        if (actor1 == NULL)
        {
            cout << "Actor not found" << endl;
            return;
        }

        Actor *actor2 = _mapActorNames[key2]->Search(actor2_name)->_value;
        if (actor2 == NULL)
        {
            cout << "Actor not found" << endl;
            return;
        }

        bool acted = 0;
        Node<Movie *> *movies = actor1->_movies;
        while (movies != NULL)
        {
            if (movies->_value->_actor1 == actor2)
            {
                cout << movies->_value->_name << endl;
                acted = 1;
            }
            if (movies->_value->_actor2 == actor2)
            {
                cout << movies->_value->_name << endl;
                acted = 1;
            }
            if (movies->_value->_actor3 == actor2)
            {
                cout << movies->_value->_name << endl;
                acted = 1;
            }
            movies = movies->_next;
        }
        if (acted == 0)
        {
            cout << "Not acted together" << endl;
        }
        return;
    }

    void searchUniqueCoActor(string actor1_name)
    {
        set<Actor *> coActors = searchCoActor(actor1_name, "noactor");
        set<Actor *>::iterator itr;
        
        for (itr = coActors.begin(); itr != coActors.end(); itr++)
        {
            cout << "Actor: " << (*itr)->_name << endl;
            Node<Movie *> *movies = (*itr)->_movies;

            while (movies != NULL)
            {
                if (movies->_value->_actor1->_name == actor1_name)
                {
                    cout << "Movie Title: " << movies->_value->_name << endl;
                    movies = movies->_next;
                    continue;
                }
                if (movies->_value->_actor2->_name == actor1_name)
                {
                    cout << "Movie Title: " << movies->_value->_name << endl;
                    movies = movies->_next;
                    continue;
                }
                if (movies->_value->_actor3->_name == actor1_name)
                {
                    cout << "Movie Title: " << movies->_value->_name << endl;
                    movies = movies->_next;
                    continue;
                }
                movies = movies->_next;
            }
            cout << endl;
        }
    }

    void ActorSearch(string name)
    {
        char key = (char)tolower(name[0]);
        ActorNode *ActorNode = _mapActorNames[key]->Search(name);
        if (ActorNode == NULL)
        {
            cout << "Actor not found" << endl;
            return;
        }
        Actor *actorData = ActorNode->_value;
        cout << "Name: " << actorData->_name << endl;
        cout << "FB Likes: " << actorData->_fBLikes << endl;
        cout << "Movies: " << endl;
        Node<Movie *> *movies = actorData->_movies;
        while (movies != NULL)
        {
            cout << "Title: " << movies->_value->_name << " Release Year: " << movies->_value->_releaseYear << endl;
            movies = movies->_next;
        }
        return;
    }

    void DirectorSearch(string name)
    {
        char key = (char)tolower(name[0]);
        DirectorNode *directorNode = _mapDirectorNames[key]->Search(name);
        if (directorNode == NULL)
        {
            cout << "Director not found" << endl;
            return;
        }
        Director *directorData = directorNode->_value;
        Node<Movie *> *movies = directorData->_movies;
        cout << "Name: " << directorData->_name << endl;
        cout << "Movies: " << endl;
        while (movies != NULL)
        {
            cout << "Title: " << movies->_value->_name << endl;
            movies = movies->_next;
        }
    }

    void DirectorSearchGenre(string genre)
    {
        
        auto itr = _mapMovieGenre.find(genre);
        if (itr == _mapMovieGenre.end())
        {
            cout << "Genre Invalid" << endl;
            return;
        }
        BST<MovieNode, Movie> *genreMovies = _mapMovieGenre[genre];
        MovieNode *movie = genreMovies->_root;

        if (movie == NULL)
        {
            cout << "No movies are directed in this genre" << endl;
            return;
        }
        else
        {
            set<string> directors;
            queue<MovieNode *> q1;
            q1.push(movie);
            while (!q1.empty())
            {
                MovieNode *movie = q1.front();
                directors.insert(movie->_value->_director->_name);
                if (movie->_left != NULL)
                {
                    q1.push(movie->_left);
                }
                if (movie->_right != NULL)
                {
                    q1.push(movie->_right);
                }
                q1.pop();
            }
            cout << directors.size() << " Directors:" << endl;
            for (auto itr = directors.begin(); itr != directors.end(); itr++)
            {
                cout << *itr << endl;
            }
            cout << endl;
        }
    }

    void SearchMovie(string name)
    {
        char key = (char)tolower(name[0]);
        auto itr = _mapMovieNames.find(key);
        if (itr == _mapMovieNames.end())
        {
            cout << "Movie Key Not Found" << endl;
            return;
        }
        MovieNode *movieNode = _mapMovieNames[key]->Search(name);
        if (movieNode == NULL)
        {
            cout << "Movie not in database" << endl;
            return;
        }

        Movie *movieData = movieNode->_value;

        cout << "Movie Title: " << movieData->_name << endl;
        cout << "Release Year: " << movieData->_releaseYear << endl;
        cout << "Score: " << movieData->_imdbScore << endl;
        cout << "Content Rating: " << movieData->_contentRating << endl;
        cout << "Duration: " << movieData->_duration << endl;
        cout << "Director: " << movieData->_director->_name << endl;
        cout << "Actor 1: " << movieData->_actor1->_name << endl;
        cout << "Actor 2: " << movieData->_actor2->_name << endl;
        cout << "Actor 3: " << movieData->_actor3->_name << endl;
    }

    void PrintMovieByYear(string movie_year)
    {
        auto itr = _mapMovieYear.find(movie_year);
        if (itr == _mapMovieYear.end())
        {
            cout << "Movie Year Not Found" << endl;
            return;
        }
        BST<MovieNode, Movie> *yearTree = _mapMovieYear[movie_year];
        yearTree->InOrderTraversal(yearTree->_root);
    }

    void PrintMoviesYearWise(bool ascending = true)
    {
        set<string> years;
        for (std::map<string, BST<MovieNode, Movie> *>::iterator it = _mapMovieYear.begin(); it != _mapMovieYear.end(); ++it)
        {
            years.insert(it->first);
        }
        if (ascending == true)
        {
            set<string>::iterator itr;
            for (itr = years.begin(); itr != years.end(); itr++)
            {
                PrintMovieByYear(*itr);
            }
        }
        else
        {
            set<string>::iterator itr;
            for (itr = years.end(); itr != years.begin(); itr--)
            {
                string movie_year = *itr;
                BST<MovieNode, Movie> *yearTree;
                yearTree = _mapMovieYear[movie_year];
                yearTree->DescendingOrder(yearTree->_root);
            }
        }
    }

    void PrintMoviesGenreWise(string genre)
    {
        auto itr = _mapMovieGenre.find(genre);
        if (itr == _mapMovieGenre.end())
        {
            cout << "Genre Invalid" << endl;
            return;
        }
        BST<MovieNode, Movie> *genreMovies = _mapMovieGenre[genre];
        genreMovies->InOrderTraversal(genreMovies->_root);
    }

    void SearchMoviesGenreWise(string genre)
    {
        auto itr = _mapMovieGenre.find(genre);
        if (itr == _mapMovieGenre.end())
        {
            cout << "Genre Invalid" << endl;
            return;
        }
        BST<MovieNode, Movie> *genreMovies = _mapMovieGenre[genre];
        genreMovies->InOrderTraversal(genreMovies->_root);
    }
};


