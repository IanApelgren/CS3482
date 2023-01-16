//You will need to add one or more typedefs and
//declarations for whatever structure you use to hold
//your ngrams. You will also need to add prototypes
//for any new methods you add to the class.

class Ngrams 
{
   private:
      int ngramSz;
      void insertNgram(std::string s);
   public:
      Ngrams(int ngramSz, WordList & wl);
      ~Ngrams();
      void addIncreasing(NgramList *);
      void addDecreasing(NgramList *);
};

