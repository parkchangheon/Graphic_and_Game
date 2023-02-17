#include<iostream>
using namespace std;

// 생성자에서 호출되는 함수가 왜 거기서 호출되는지 아나?

// 정면의 몬스터 정보를 어떻게 불러올 것인가?



//1) 

/*
Unreal Engine에서 Createdefaultsubobject 함수는 UObject의 서브 오브젝트를 생성하는 함수.
이 함수는 일반적으로 AActor와 같은 UObject의 파생 클래스에서 사용된다.
Createdefaultsubobject 함수는 다른 UObject를 멤버 변수로 가지는 UObject를 생성할 때 사용된다.

Createdefaultsubobject 함수가 생성자에서 호출되는 이유는 이 함수를 사용하여 멤버 변수를 초기화할 때, 해당 멤버 변수가 생성자에서 생성되어야 하기 때문. 
일반적으로 UObject의 멤버 변수는 생성자에서 생성되며, 이후 Createdefaultsubobject 함수를 사용하여 생성된 UObject를 이 멤버 변수에 할당합니다.

그렇다면, Createdefaultsubobject 함수를 생성자 이외의 다른 함수에서 사용하는 것이 가능한가요? 일반적으로는 가능합니다. 하지만 UObject가 초기화되기 이전에 호출되면 예상치 못한 결과를 낼 수 있으므로 주의해야 합니다. Createdefaultsubobject 함수를 사용하여 생성된 UObject는 그것을 소유하는 UObject와 함께 파괴되므로, Createdefaultsubobject 함수를 호출한 함수가 생성된 UObject에 대한 소유권을 가지고 있어야 합니다.

결론적으로, Createdefaultsubobject 함수는 UObject를 초기화하기 위해 생성자에서 호출되며, UObject의 멤버 변수를 초기화하는 데 중요한 역할을 합니다. Createdefaultsubobject 함수를 생성자 이외에서 사용할 때는 주의가 필요하며, 생성된 UObject의 소유권에 대한 책임이 있습니다.
*/



//2)
/*
Line Trace 방법
Line Trace 방법은 캐릭터의 시야 방향에 직선을 그어 해당 위치에 있는 오브젝트를 검색하는 방법입니다.이 방법은 해당 위치에 있는 모든 오브젝트를 찾을 수 있기 때문에, 
여러 개의 몬스터가 있을 때 가장 가까운 몬스터를 선택하려면 거리 계산을 추가로 해주어야 합니다.

Sphere Trace 방법
Sphere Trace 방법은 Line Trace와 비슷하지만, 일정 반경 내에 있는 모든 오브젝트를 검색하는 방법입니다.
이 방법은 Line Trace보다 더 많은 검색 범위를 가지므로, 여러 몬스터가 있을 때 가장 가까운 몬스터를 선택하기 더 쉬울 수 있습니다.

Overlap Sphere 방법
Overlap Sphere 방법은 일정 반경 내에 있는 모든 오브젝트와 충돌 검사를 하는 방법입니다.Overlap Sphere는 콜리전 검사를 하는 것이기 때문에, 캐릭터와 몬스터의 콜리전 설정이 필요합니다.

위의 방법들 중에서 선택하여 사용할 수 있으며, 몬스터의 정보를 불러오는 방법은 개발자의 필요에 따라 다양합니다.각 방법은 검색 속도, 정확도, 구현의 복잡도 등을 고려하여 선택하면 됩니다.
*/


