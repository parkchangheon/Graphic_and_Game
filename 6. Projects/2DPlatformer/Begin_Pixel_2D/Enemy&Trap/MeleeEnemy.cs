using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MeleeEnemy : MonoBehaviour
{
    [SerializeField] private float attackCooldown;
    [SerializeField] private float range;
    [SerializeField] private int damage;
    [SerializeField] private BoxCollider2D boxCollider;
    [SerializeField] private LayerMask playerLayer;
    private float cooldownTimer = Mathf.Infinity;

    private void Update()
    {
        cooldownTimer += Time.deltaTime;

        //Attack when only player is in sight
        if(PlayerInsight())
        {
            if (cooldownTimer > attackCooldown)
            {
                // Attack

            }
        }

    }

    private bool PlayerInsight()
    {  
        // transform.right * range 는 빨간색 박스를 range만큼 움직이게 하기 위함이다.
        // localScale.x를 한것은, 오른쪽 왼쪽일때, 플립을 해주기 위함.
        RaycastHit2D hit = Physics2D.BoxCast(boxCollider.bounds.center + -transform.right * range * transform.localScale.x, 
            boxCollider.bounds.size, 0, Vector2.left, 0, playerLayer);   //origin, size, angle, direction
        return hit.collider != null;
    }

    private void OnDrawGizmos() // 
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireCube(boxCollider.bounds.center + -transform.right * range * transform.localScale.x, boxCollider.bounds.size);
    }
}
