#pragma once

class Repository;

namespace Controller {

class AbstractController {
public:
    AbstractController(Repository* repository);

private:
    Repository* m_repository = nullptr;
};

}
