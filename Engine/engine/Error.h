//
// Created by Alexandre Tolstenko Nogueira on 3/20/18.
//

#ifndef ENGINE_ERROR_H
#define ENGINE_ERROR_H


class NotImplementedException : public std::exception {
public:

  // Construct with given error message:
  NotImplementedException(const char * error = "Functionality not yet implemented!")
  {
    errorMessage = error;
  }

  // Provided for compatibility with std::exception.
  const char * what() const noexcept
  {
    return errorMessage.c_str();
  }

private:

  std::string errorMessage;
};

#endif //ENGINE_ERROR_H
