#include <iostream>

#include "AppClass.h"

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    AppClass app_class(nullptr);
    app_class.build(); return app_class.execute();
}
