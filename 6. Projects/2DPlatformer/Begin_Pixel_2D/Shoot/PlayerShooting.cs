using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerShooting: MonoBehaviour
{
    [SerializeField]private float shootCooldown;
    [SerializeField] private Transform firePoint; //
    [SerializeField] private GameObject[] fireballs; //생성한 10개의 fireball(풀이랍시고 만들어놓은거에서 가져오기 위한 배열)


    private Animator anim;
    private PlayerMovement playerMovement;
    private float cooldownTimer = Mathf.Infinity;

    private void Awake()
    {
        anim = GetComponent<Animator>();
        playerMovement = GetComponent<PlayerMovement>();
    }

    private void Update()
    {
        if (Input.GetMouseButton(0) && (cooldownTimer > shootCooldown) && playerMovement.canShoot())
            Shoot();

        cooldownTimer += Time.deltaTime;
    }

    private void Shoot()
    {

        anim.SetTrigger("shoot");
        cooldownTimer = 0; //시작할때 바로 공격을 못하게끔 하는 조치
        //pool (Object Pool)
        // =>성능을 확보시키기 위해 사용함.
        // 오브젝트를 생성하고 파괴하는 작업은 꽤나 무거운 작업으로 분류됨.
        // 오브젝트 생성은 메모리를 새로 할당하고 리소스를 로드하는 등의 초기화 과정으로,
        // 파괴 이후 발생하는 가비지 컬렉팅으로 인한 프레임 드랍이 발생할 수 있다.
        // 게임에 필요한 오브젝트를 미리 생성해서 필요할때마다 꺼내쓰고, 끝나면 다시 풀에 돌려줌 
        // 파괴가 아닌 게임이 시작될떄 필요한만큼의 오브젝트만 생성하고 모자라면 추가 생성하고 끝나면 파괴하는 방식.

        fireballs[FindFireball()].transform.position = firePoint.position;
        fireballs[FindFireball()].GetComponent<Projectile>().SetDirection(Mathf.Sign(transform.localScale.x));
    }

    private int FindFireball() //deactivate 시켜준것 찾는 메소드
    {
        for(int i=0;i<fireballs.Length;i++)
        {
            if (!fireballs[i].activeInHierarchy)
                return i;
        }
        return 0;
    }
}
