
using UnityEngine;
using System.Collections;

public class FireTrap : MonoBehaviour
{
    [SerializeField] private float damage;


    [Header("Firetrap Timers")] // GUI에서 섹션 header를 볼 수 있게끔 함.(언리얼 Category 같은 느낌?
    [SerializeField] private float activationDelay;
    [SerializeField] private float activeTime;
    private Animator anim;
    private SpriteRenderer spriteRend;

    private bool triggered;
    private bool active;

    private void Awake()
    {
        anim = GetComponent<Animator>();
        spriteRend = GetComponent<SpriteRenderer>();
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag == "Player")
        {


            if(!triggered)
            {
                //trigger the firetrap
                StartCoroutine(ActivateFiretrap());
            }

            if(active)
                collision.GetComponent<Health>().TakeDamage(damage);
        }
    }

    private IEnumerator ActivateFiretrap()
    {
        triggered = true;
        spriteRend.color = Color.red;

        yield return new WaitForSeconds(activationDelay);
        spriteRend.color = Color.white;
        active = true;
        anim.SetBool("activated", true);

        yield return new WaitForSeconds(activeTime);
        active = false;
        triggered = false;
        anim.SetBool("activated", false);

    }

}



/*유니티 코루틴
함수를 호출하면 값을 반환하기 전에 실행 완료가 된다.
이는 함수에서 수행되는 모든 액션이 하나의 프레임 업데이트 내에서 발생해야하는 것을 의미

예를 들어 아래와 같은 코드가 있다고 하면,
    void Fade() {
    for (float f = 1f; f >= 0; f -= 0.1f)
    {
        Color c = renderer.material.color;
        c.a = f;
        renderer.material.color = c;
    }
}

페이드 함수는 제 기능을 하지 못한다. 
페이딩을 보기 위해 중간 값이 렌더링 중임을 나타내기 위해 프레임 시퀀스에 대해 알파를 줄여야함.
중간 값은 절대 보이지 않으며 객체는 즉시 사라진다.

프레임 단위로 페이드를 실행하는 코드를 update 함수에 추가하여 이런 상황을 처리할 수 있다.
하지만 이런 작업에 코루틴을 사용하는 것이 더 편하다.

코루틴은 실행을 일시 중지하고 unity에 제어 권한을 반환하고, 프레임에서 중단했던 위치에서 계속할 수 있다.

즉 

    Ienumerator Fade() {
    for (float f = 1f; f >= 0; f -= 0.1f)
    {
        Color c = renderer.material.color;
        c.a = f;
        renderer.material.color = c;
        yield return null;
    }
}

위 코드에서 IEnumerator 반환 타입과 바디 어딘가에 포함된 yield 반환문으로 선언된것을 볼 수 있는데,
yield 반환 라인은 실행이 일시 중지되고 다음 프레임에서 다시 시작 되는 지점이다.*/