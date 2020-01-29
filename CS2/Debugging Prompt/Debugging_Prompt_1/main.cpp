// Comments go here. Blah, blah, blah

#include <vector>
#include <iostream>

struct Student_info
{
    int score;
};

std::vector<Student_info> takeFails(std::vector<Student_info>& students);

int main()
{
    std::cout << "Start!" << std::endl;

    Student_info s1, s2, s3, s4, s5;
    s1.score = 90;
    s2.score = 75;
    s3.score = 60;
    s4.score = 50;
    s5.score = 30;
    std::vector<Student_info> myVec;
    //myVec.push_back(s1);
    //myVec.push_back(s4);
    //myVec.push_back(s2);
    //myVec.push_back(s5);
    //myVec.push_back(s3);

    myVec.push_back(s1);
    myVec.push_back(s2);
    myVec.push_back(s3);
    myVec.push_back(s4);
    myVec.push_back(s5);

    std::cout << "All scores:";
    for (int y = 0; y < myVec.size(); ++y)
    {
        std::cout << " " << myVec.at(y).score;
    }
    std::cout << std::endl;

    std::vector<Student_info> passVec = takeFails(myVec);

    std::cout << "Passing scores:";
    for (int x = 0; x < passVec.size(); ++x)
    {
        std::cout << " " << passVec.at(x).score;
    }
    std::cout << std::endl;

    std::cout << "Finish!" << std::endl;
    return 0;
}

bool fgrade(std::vector<Student_info>::iterator &iterPtr)
{
    return (*iterPtr).score >= 60;
}

std::vector<Student_info> takeFails(std::vector<Student_info>& students)
{
  std::vector<Student_info> fail;
  std::vector<Student_info>::iterator iter = students.begin(), endIter = students.end();

  while (iter != endIter)
  {
    if (fgrade(iter))
    {
      fail.push_back(*iter);
      iter = students.erase(iter);
    }
    else
    {
      ++iter;
    }
  }

  return fail;
}
