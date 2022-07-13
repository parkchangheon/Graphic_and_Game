using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RangedEnemy : MonoBehaviour
{
    [Header("attack parameter")]
    [SerializeField] private float attackCooldown;
    [SerializeField] private float range;
    [SerializeField] private int damage;

    [Header("Ranged Attack")]
    [SerializeField] private Transform firepoint;
    [SerializeField] private GameObject[] fireball;

    [Header("Collider Parameter")]
    [SerializeField] private float colliderDistance;
    [SerializeField] private BoxCollider2D boxCollider;

    [Header("Player Layer")]
    [SerializeField] private LayerMask playerLayer;
    private float cooldownTimer = Mathf.Infinity;

    //reference
    private Animator anim;
    private EnemyPatrol enemyPatrol;

    private void Awake()
    {
        anim = GetComponent <Animator>();
        enemyPatrol = GetComponentInParent<EnemyPatrol>();
    }

    private void Update()
    {
        cooldownTimer += Time.deltaTime;

        //Attack only when player in sight
        if(PlayerInsight())
        {
            if(cooldownTimer >= attackCooldown)
            {
                cooldownTimer = 0;
                anim.SetTrigger("RangedAttack");
            }
        }

        if (enemyPatrol != null)
            enemyPatrol.enabled = !PlayerInsight();
    }

    private void RangedAttack()
    {
        cooldownTimer = 0;

        //shoot projectile
        fireball[FindFireball()].transform.position = firepoint.position;
        fireball[FindFireball()].GetComponent<EnemyProjectile>().ActivateProjectile();
    }

    private int FindFireball()
    {
        for(int i=0;i<fireball.Length;i++)
        {
            if (!fireball[i].activeInHierarchy)
                return i;
        }
        return 0;
    }

    private bool PlayerInsight()
    {
        RaycastHit2D hit = Physics2D.BoxCast(boxCollider.bounds.center + -transform.right * range * transform.localScale.x * colliderDistance,
            new Vector3(boxCollider.bounds.size.x * range, boxCollider.bounds.size.y, boxCollider.bounds.size.z),
            0, Vector2.left, 0, playerLayer);   //origin, size, angle, direction

        return hit.collider != null;
    }


    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireCube(boxCollider.bounds.center + -transform.right * range * transform.localScale.x * colliderDistance,
            new Vector3(boxCollider.bounds.size.x * range, boxCollider.bounds.size.y, boxCollider.bounds.size.z));
    }

}
