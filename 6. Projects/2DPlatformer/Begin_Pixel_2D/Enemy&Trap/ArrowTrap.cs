using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ArrowTrap : MonoBehaviour
{
    [SerializeField] private float attackCooldown;
    [SerializeField] private Transform firePoint;
    [SerializeField] private GameObject[] arrows;
    private float CooldownTimer;
    private void Attack()
    {
        CooldownTimer = 0;
        arrows[FindArrowl()].transform.position = firePoint.position;   // fireball position setting
        arrows[FindArrowl()].GetComponent<EnemyProjectile>().ActivateProjectile();  //fireball projectile direction setting
    }

    private int FindArrowl()
    {
        for(int i=0;i< arrows.Length;i++)
        {
            if (!arrows[i].activeInHierarchy)      //fireballs[i].setActive에 따라 상황이 변하며, 부모가 있다면, 부모를 따른다. (부모가 active false 이면 자식도 false)
            { //예를 들어 게임 오브젝트가 selfActive = true인데, activeinHierarchy 값이 false 이면, 오브젝트의 부모 오브젝트가 활성화 되지 않았다라는 말. 
                return i;
            }
        }
        return 0;  //fireball이 없으면 0을 리턴한다.
    }

    private void Update()
    {
        CooldownTimer += Time.deltaTime;

        if (attackCooldown <= CooldownTimer)
            Attack();
        
    }

}
