using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MeleeEnemy : MonoBehaviour
{
    [Header("Attack Parameter")]
    [SerializeField] private float attackCooldown;
    [SerializeField] private float range;
    [SerializeField] private int damage;

    [Header("Collider Parameter")]
    [SerializeField] private float colliderDistance;
    [SerializeField] private BoxCollider2D boxCollider;
    
    [Header("Player Layer")]
    [SerializeField] private LayerMask playerLayer;
    private float cooldownTimer = Mathf.Infinity;
    private Animator anim;

    private Health PlayerHealth;

    private EnemyPatrol enemyPatrol;


    private void Awake()
    {
        anim = GetComponent<Animator>();
        enemyPatrol = GetComponentInParent<EnemyPatrol>();
    }


    private void Update()
    {
        cooldownTimer += Time.deltaTime;

        //Attack when only player is in sight
        if(PlayerInsight())
        {
            if (cooldownTimer > attackCooldown)
            {
                // Attack
                cooldownTimer = 0; //적이 방금 공격을 했으니, 쿨다운 타이머를 초기화해준다.
                anim.SetTrigger("MeleeAttack");
            }
        }

        if (enemyPatrol != null)
            enemyPatrol.enabled = !PlayerInsight();

    }

    private bool PlayerInsight()
    {  
        // transform.right * range 는 빨간색 박스를 range만큼 움직이게 하기 위함이다.
        // localScale.x를 한것은, 오른쪽 왼쪽일때, 플립을 해주기 위함.
        RaycastHit2D hit = Physics2D.BoxCast(boxCollider.bounds.center + -transform.right * range * transform.localScale.x * colliderDistance, 
            new Vector3(boxCollider.bounds.size.x * range, boxCollider.bounds.size.y, boxCollider.bounds.size.z), 
            0, Vector2.left, 0, playerLayer);   //origin, size, angle, direction
        if (hit.collider != null)
        {
            PlayerHealth = hit.transform.GetComponent<Health>();
        }

        return hit.collider != null;



    }

    private void OnDrawGizmos() // 
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireCube(boxCollider.bounds.center + -transform.right * range * transform.localScale.x * colliderDistance,
             new Vector3(boxCollider.bounds.size.x * range, boxCollider.bounds.size.y, boxCollider.bounds.size.z));
    }


    private void DamagePlayer()
    {
        if (PlayerInsight())
        {
            //Damage player health
            PlayerHealth.TakeDamage(damage);
        }
    }
}
