
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private float speed;
    [SerializeField] private float JumpPower;

    [SerializeField] private LayerMask groundLayer;
    [SerializeField] private LayerMask wallLayer;

    private float horizontalInput;
    private Rigidbody2D body;
    private Animator anim;
    //private bool grounded;
    private BoxCollider2D boxcollider;

    private float wallJumpCoolDownn;

    private void Awake()
    {
        //Grab reference!
        body = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
        boxcollider = GetComponent<BoxCollider2D>();
    }

    private void Update()
    {
        horizontalInput = Input.GetAxis("Horizontal");

        //Flip Method
        if (horizontalInput >= 0.01f)
            transform.localScale = Vector3.one*5;

        else if (horizontalInput < -0.01f)
            transform.localScale = new Vector3(-1*5, 1*5, 1);


        //set Animation Paramete
        anim.SetBool("IsRunning", horizontalInput != 0);
        anim.SetBool("Grounded", IsGrounded());

        //WallJump
        if (wallJumpCoolDownn > 0.2f)
        {
            //jump Method
            if (Input.GetKey(KeyCode.Space))
                Jump();
            body.velocity = new Vector3(Input.GetAxis("Horizontal") * speed, body.velocity.y);

            if (onWall() && !IsGrounded())
            {
                body.gravityScale = 0;
                body.velocity = Vector2.zero;
            }
            else
                body.gravityScale = 3;
        }
        else
            wallJumpCoolDownn += Time.deltaTime;

        print(onWall());
    }

    private void Jump()
    {
        if(IsGrounded())
        {
            body.velocity = new Vector2(body.velocity.x, JumpPower);
            anim.SetTrigger("Jump");
        }
        else if(onWall() && !IsGrounded())
        {
            if(horizontalInput == 0)
            {
                body.velocity = new Vector2(-Mathf.Sign(transform.localScale.x) * 10, 0);  //-인 이유는 벽을 보고 있는 곳에서 나가려고
                transform.localScale = new Vector3(-Mathf.Sign(transform.localScale.x), transform.localScale.y, transform.localScale.z);
            }
            else
                body.velocity = new Vector2(-Mathf.Sign(transform.localScale.x) * 3, 6);  //-인 이유는 벽을 보고 있는 곳에서 나가려고

            wallJumpCoolDownn = 0;
        }
    }


    private bool IsGrounded()
    {
        RaycastHit2D raycastHit = Physics2D.BoxCast(boxcollider.bounds.center, boxcollider.bounds.size, 0, Vector2.down, 0.1f, groundLayer);
        return raycastHit.collider != null;
    }
    private bool onWall()
    {
        RaycastHit2D raycastHit = Physics2D.BoxCast(boxcollider.bounds.center, boxcollider.bounds.size, 0, new Vector2(transform.localScale.x, 0), 0.1f, wallLayer);
        return raycastHit.collider != null;
    }

    public bool canAttack()
    {
        return horizontalInput == 0 && IsGrounded();
    }

    public bool canShoot()
    {
        return horizontalInput == 0 && IsGrounded() && !onWall();
    }
}
